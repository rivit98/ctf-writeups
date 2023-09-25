// SPDX-License-Identifier: LGPL-3.0-only
pragma solidity >=0.7.0 <0.9.0;

/// @title Proxied - indicates that a contract will be proxied. Also defines storage requirements for Proxy.
/// @author Alan Lu - <alan@gnosis.pm>
contract Proxied {
    address public masterCopy;
}

/// @title Proxy - Generic proxy contract allows to execute all transactions applying the code of a master contract.
/// @author Stefan George - <stefan@gnosis.pm>
contract Proxy is Proxied {
    function setAddr(address n) external {
        masterCopy = n;
    }

    /// @dev Fallback function forwards all transactions and returns all received return data.
    function _fallback() internal {
        assembly {
            // dddc5bbf
            mstore(0, "AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD")
            mstore8(0, 0xdd)
            mstore8(1, 0xdc)
            mstore8(2, 0x5b)
            mstore8(3, 0xbf)
            mstore8(34, 0x0d)
            mstore8(35, 0xad)
            revert(0, 0x24)
        }

        // mstore(0x80,((mload(0x80) + var4) - balance(this.address)));
        // 03C6 - target
        // 2e4
//        '0xdad'


//        address _masterCopy = masterCopy;
//        assembly {
//            calldatacopy(0, 0, calldatasize())
//            let success := delegatecall(not(0), _masterCopy, 0, calldatasize(), 0, 0)
//            returndatacopy(0, 0, returndatasize())
//            switch success
//                case 0 {
//                    revert(0, returndatasize())
//                }
//                default {
//                    return(0, returndatasize())
//                }
//        }
    }

    /**
     * @dev Fallback function that delegates calls to the masterCopy.
     * Runs when no other function in the contract matches the call data.
     */
    fallback () external payable {
        _fallback();
    }

    /**
     * @dev Fallback function that receives ether and delegates calls to masterCopy.
     * Runs when call data is empty.
     */
    receive () external payable {
        _fallback();
    }
}