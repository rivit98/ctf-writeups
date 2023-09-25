pragma solidity >=0.7.0 <0.9.0;

contract Factory {
    event Deployed(address addr, uint256 salt);

    function deploy(bytes memory code, uint256 salt) public {
        address addr;

        assembly {
            addr := create2(0, add(code, 0x20), mload(code), salt)
            if iszero(extcodesize(addr)) {
                revert(0, 0)
            }
        }

        emit Deployed(addr, salt);
    }

    function getAddress(bytes memory bytecode, uint _salt)
    public
    view
    returns (address)
    {
        bytes32 hash = keccak256(
            abi.encodePacked(bytes1(0xff), address(this), _salt, keccak256(bytecode))
        );

        // NOTE: cast last 20 bytes of hash to address
        return address(uint160(uint(hash)));
    }
}