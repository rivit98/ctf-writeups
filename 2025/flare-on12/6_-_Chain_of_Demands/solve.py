from web3 import Web3
from Crypto.Util.number import bytes_to_long, long_to_bytes, isPrime, inverse

rpc_url = "https://0xrpc.io/sep"
private_key = "0x6b4abeb307d59242141532388fef03bdea9531e5fdce1e9e4488c232de00056b"

def deployed_contract(addr, contract_abi):
    w3 = Web3(Web3.HTTPProvider(rpc_url))
    deployed_contract = w3.eth.contract(address=addr, abi=contract_abi)
    return deployed_contract


class LCGOracle:
    def __init__(self, multiplier, increment, modulus, initial_seed):
        self.multiplier = multiplier
        self.increment = increment
        self.modulus = modulus
        self.state = initial_seed
        self.contract_bytes = '6080604052348015600e575f5ffd5b506102e28061001c5f395ff3fe608060405234801561000f575f5ffd5b5060043610610029575f3560e01c8063115218341461002d575b5f5ffd5b6100476004803603810190610042919061010c565b61005d565b6040516100549190610192565b60405180910390f35b5f5f848061006e5761006d6101ab565b5b86868061007e5761007d6101ab565b5b8987090890505f5f8411610092575f610095565b60015b60ff16905081816100a69190610205565b858260016100b49190610246565b6100be9190610205565b6100c89190610279565b9250505095945050505050565b5f5ffd5b5f819050919050565b6100eb816100d9565b81146100f5575f5ffd5b50565b5f81359050610106816100e2565b92915050565b5f5f5f5f5f60a08688031215610125576101246100d5565b5b5f610132888289016100f8565b9550506020610143888289016100f8565b9450506040610154888289016100f8565b9350506060610165888289016100f8565b9250506080610176888289016100f8565b9150509295509295909350565b61018c816100d9565b82525050565b5f6020820190506101a55f830184610183565b92915050565b7f4e487b71000000000000000000000000000000000000000000000000000000005f52601260045260245ffd5b7f4e487b71000000000000000000000000000000000000000000000000000000005f52601160045260245ffd5b5f61020f826100d9565b915061021a836100d9565b9250828202610228816100d9565b9150828204841483151761023f5761023e6101d8565b5b5092915050565b5f610250826100d9565b915061025b836100d9565b9250828203905081811115610273576102726101d8565b5b92915050565b5f610283826100d9565b915061028e836100d9565b92508282019050808211156102a6576102a56101d8565b5b9291505056fea2646970667358221220c7e885c1633ad951a2d8168f80d36858af279d8b5fe2e19cf79eac15ecb9fdd364736f6c634300081e0033'
        self.contract_abi = [{'inputs': [{'internalType': 'uint256', 'name': 'LCG_MULTIPLIER', 'type': 'uint256'}, {'internalType': 'uint256', 'name': 'LCG_INCREMENT', 'type': 'uint256'}, {'internalType': 'uint256', 'name': 'LCG_MODULUS', 'type': 'uint256'}, {'internalType': 'uint256', 'name': '_currentState', 'type': 'uint256'}, {'internalType': 'uint256', 'name': '_counter', 'type': 'uint256'}], 'name': 'nextVal', 'outputs': [{'internalType': 'uint256', 'name': '', 'type': 'uint256'}], 'stateMutability': 'pure', 'type': 'function'}]
        self.deployed_contract = deployed_contract('0xE902BF5fF2eeCa15E086Ddea4628ea6704840b28', self.contract_abi)

    def get_next(self, counter):
        print(f'\n[+] Calling nextVal() with _currentState={self.state}')
        self.state = self.deployed_contract.functions.nextVal(self.multiplier, self.increment, self.modulus, self.state, counter).call()
        print(f'  _counter = {counter}: Result = {self.state}')
        return self.state

class TripleXOROracle:
    def __init__(self):
        self.contract_bytes = '61030f61004d600b8282823980515f1a6073146041577f4e487b71000000000000000000000000000000000000000000000000000000005f525f60045260245ffd5b305f52607381538281f3fe7300000000000000000000000000000000000000003014608060405260043610610034575f3560e01c80636230075614610038575b5f5ffd5b610052600480360381019061004d919061023c565b610068565b60405161005f91906102c0565b60405180910390f35b5f5f845f1b90505f845f1b90505f61007f85610092565b9050818382181893505050509392505050565b5f5f8290506020815111156100ae5780515f525f5191506100b6565b602081015191505b50919050565b5f604051905090565b5f5ffd5b5f5ffd5b5f819050919050565b6100df816100cd565b81146100e9575f5ffd5b50565b5f813590506100fa816100d6565b92915050565b5f5ffd5b5f5ffd5b5f601f19601f8301169050919050565b7f4e487b71000000000000000000000000000000000000000000000000000000005f52604160045260245ffd5b61014e82610108565b810181811067ffffffffffffffff8211171561016d5761016c610118565b5b80604052505050565b5f61017f6100bc565b905061018b8282610145565b919050565b5f67ffffffffffffffff8211156101aa576101a9610118565b5b6101b382610108565b9050602081019050919050565b828183375f83830152505050565b5f6101e06101db84610190565b610176565b9050828152602081018484840111156101fc576101fb610104565b5b6102078482856101c0565b509392505050565b5f82601f83011261022357610222610100565b5b81356102338482602086016101ce565b91505092915050565b5f5f5f60608486031215610253576102526100c5565b5b5f610260868287016100ec565b9350506020610271868287016100ec565b925050604084013567ffffffffffffffff811115610292576102916100c9565b5b61029e8682870161020f565b9150509250925092565b5f819050919050565b6102ba816102a8565b82525050565b5f6020820190506102d35f8301846102b1565b9291505056fea26469706673582212203fc7e6cc4bf6a86689f458c2d70c565e7c776de95b401008e58ca499ace9ecb864736f6c634300081e0033'
        self.contract_abi = [{'inputs': [{'internalType': 'uint256', 'name': '_primeFromLcg', 'type': 'uint256'}, {'internalType': 'uint256', 'name': '_conversationTime', 'type': 'uint256'}, {'internalType': 'string', 'name': '_plaintext', 'type': 'string'}], 'name': 'encrypt', 'outputs': [{'internalType': 'bytes32', 'name': '', 'type': 'bytes32'}], 'stateMutability': 'pure', 'type': 'function'}]
        self.deployed_contract = deployed_contract('0x61BC244B2e2b158dAb7b3a239cecd28B898fEaE3', self.contract_abi)

    def encrypt(self, prime_from_lcg, conversation_time, plaintext_bytes):
        print(f'\n[+] Calling encrypt() with prime_from_lcg={prime_from_lcg}, time={conversation_time}, plaintext={plaintext_bytes}')
        ciphertext = self.deployed_contract.functions.encrypt(prime_from_lcg, conversation_time, plaintext_bytes).call()
        print(f'  _ciphertext = {ciphertext.hex()}')
        return ciphertext


lcg_oracle = LCGOracle(
    67192040330448629411569469148996452347135994600540722067180373767878044185647,
    99227336246447563326081778635314136420514626764135112597502806801041930961679,
    70162817795225084397164488661004836433247754877528881959579355413849190882383,
    33997266682902850140225272282449387868635715365752160122430153597255539852627
    )

triplexororacle = TripleXOROracle()


# print(lcg_oracle.get_next(0)) # 33997266682902850140225272282449387868635715365752160122430153597255539852627
# print(lcg_oracle.get_next(1)) # 55459398888864594124105527272161457001600610327087351274753678381990760219974
# print(lcg_oracle.get_next(2)) # 21787785015775945936298352415655924554294352090167527505829217478816505147827
# print(lcg_oracle.get_next(4)) # 32689147892154307209485352861731363187854384835524361135032795051347904009136
# print(lcg_oracle.get_next(123123)) # 18466055061696993760809299688536505607426985463405981930746629095073800788009


"""
55459398888864594124105527272161457001600610327087351274753678381990760219974
21787785015775945936298352415655924554294352090167527505829217478816505147827
32689147892154307209485352861731363187854384835524361135032795051347904009136
18466055061696993760809299688536505607426985463405981930746629095073800788009
31116232533566225669959912640519910106582055783883513717936457223170660432075
3961705060103867175182148420284518771577967243283905206904397174419999372743
70162817795225084397164488661004836433247754877528881959579355413849190882383
67192040330448629411569469148996452347135994600540722067180373767878044185647
"""


# ciphertext = triplexororacle.encrypt(0x1337,0, 'AAAA')
# print(ciphertext)

ciphertext = b'AAAA\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x137'


def triple_xor_recover_lcg(plaintext, conversation_time, ciphertext):
    plaintext_bytes = plaintext.encode()
    if len(plaintext_bytes) < 32:
        plaintext_bytes = plaintext_bytes + b'\x00' * (32 - len(plaintext_bytes))
    elif len(plaintext_bytes) > 32:
        raise ValueError("Plaintext too long")

    ciphertext_bytes = bytes.fromhex(ciphertext.hex())
    if len(ciphertext_bytes) != 32:
        raise ValueError("Ciphertext must be 32 bytes")

    recovered_lcg_output = int.from_bytes(bytes(a ^ b ^ c for a, b, c in zip(plaintext_bytes, conversation_time.to_bytes(32, 'big'), ciphertext_bytes)), 'big')
    return recovered_lcg_output


print(triple_xor_recover_lcg('AAAA', 0, ciphertext))


import json
chat_log = json.load(open('chat_log.json'))

messages = chat_log[:-2]

lcg_outputs = []
for m in messages:
    conversation_time = m['conversation_time']
    plaintext = m['plaintext']
    ciphertext = bytes.fromhex(m['ciphertext'])
    recovered_lcg_output = triple_xor_recover_lcg(plaintext, conversation_time, ciphertext)
    print(f'  LCG output: {recovered_lcg_output}')
    lcg_outputs.append(recovered_lcg_output)


from crack_lcg import crack_unknown_modulus

print('\n[+] Cracking LCG parameters from recovered outputs...')
modulus, multiplier, increment = crack_unknown_modulus(lcg_outputs)
print(f'  Cracked LCG parameters:')
print(f'    Modulus:    {modulus}')
print(f'    Multiplier: {multiplier}')
print(f'    Increment:  {increment}')

lcg_oracle = LCGOracle(
    multiplier,
    increment,
    modulus,
    lcg_outputs[0]
    )

# print(lcg_oracle.get_next(0))
# print(lcg_oracle.get_next(1))
# print(triplexororacle.encrypt(lcg_oracle.get_next(1), 4, "How are you?"))



def generate_rsa_key_from_lcg():
    from crack_lcg import prng_lcg
    lcg = prng_lcg()
    lcg.m = multiplier
    lcg.c = increment
    lcg.n = modulus
    lcg.state = lcg_outputs[0]

    print('[RSA] Generating RSA key from on-chain LCG primes...')
    primes_arr = []
    rsa_msg_count = 0
    iteration_limit = 10000
    iterations = 0
    while len(primes_arr) < 8 and iterations < iteration_limit:
        if iterations == 0:
            candidate = lcg_outputs[0]
        else:
            candidate = lcg.next()
        # orig_candidate = lcg_oracle.get_next(rsa_msg_count)
        orig_candidate = None
        print(f'[RSA]  - LCG output #{rsa_msg_count + 1}: {candidate == orig_candidate} {candidate} vs {orig_candidate}')
        rsa_msg_count += 1
        iterations += 1
        if candidate.bit_length() == 256 and isPrime(candidate):
            primes_arr.append(candidate)
            print(f'[RSA]  - Found 256-bit prime #{len(primes_arr)}')
    print('Primes Array: ', primes_arr)
    if len(primes_arr) < 8:
        error_msg = '[RSA] Error: Could not find 8 primes within iteration limit.'
        print('Current Primes: ', primes_arr)
        print(error_msg)
        return error_msg
    n = 1
    for p_val in primes_arr:
        n *= p_val
    phi = 1
    for p_val in primes_arr:
        phi *= p_val - 1
    e = 65537
    d = inverse(e, phi)
    print(f'[RSA] Generated RSA key parameters:')
    print(f'  e: {e}')
    print(f'  d: {d}')
    print(f'  n: {n}')

    return d, n


d,n  = generate_rsa_key_from_lcg()

rsa_messages = chat_log[-2:]
for m in rsa_messages:
    ciphertext = bytes.fromhex(m['ciphertext'])

    ciphertext_int = int.from_bytes(ciphertext, 'little')
    plaintext_int = pow(ciphertext_int, d, n)
    plaintext_bytes = long_to_bytes(plaintext_int)
    print(f'\n[+] Decrypted RSA message: {plaintext_bytes}')
