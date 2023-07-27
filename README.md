# God-Plays-Dices
## A Proof-of-Randomness consensus protocol for blochchains

Einstein once questioned the ture randomness of quantum measurement as "God never play dice". However,  quantum randomness is proved by a huge number of experiments and we know that **God does play dices**. 

Nowdays, small-size quantum random number generator (QRNG) chip has been invented and millions of QRNG Chips are integrated into smart phones, such as Samsung Galaxy Quantum 1-3. 

We have already developed a quantum USB-key device, called Quakey. It is indeed a blockchain hardare wallet with a QRNG chip, which runs standard ECC for blockchains while replace all pseudo random numbers by quantum random numbers. We give the serial port commands to contorl Quakey in **Commands.md**

Some projects using our Quakey to give digital signature to files, especially AIGC iamges, are listed below

https://github.com/stereoF/artBox (for all systems), 
https://github.com/jiayouww/artBox_Win (only for Windows).

Since QRNG is a physical device, it is not only a soucre of ture random numbers, but also a soucre of ture fairness. This is the realism meaning of **GOD PLAYS DICE**. 

For this reason, we invented a proof-of-randomness (PoR) protocol for blockchain consensus, and uploaded it to arXiv: https://arxiv.org/abs/2211.15417 

In blockchains, the proof-of-work (PoW) consensus requires expensive hardwares which waste electricity energy a lot. It means only some big nodes with huge computing power could compete the rights of recording new blocks. Altrough the proof-of-stake (PoS) consensus can save 99% energy cost compared to PoW, it requiers staking of crypto currency to compete the rights of recording new blocks. The wining probility of a node is proptional to the amount of crypto currency it has, which makes super rich nodes and maximum extractable value (MEV) attack usually happen in PoS. Therefore, both PoW and PoS do NOT care about fairness now. They all betray the original will of decentralizion. 

PoR consensus could bring true fairness to blockchians. It is indeed a decentralized lottery algorithm. A low cost hardare wallet (Quakey) is the only required device. Everyone could compete the rights of recording new blocks with only one Quakey. It could be a popularization revolution of blockchains and opens a massive adoption door to Web3. 

For this revolution, we have a plan:

### 1. QuaKey hardware wallet

- [x] USB Hardware of QuaKey (serial port commands is showed in Commands.md)

- [x] Public key generation and digital signature

- [ ] SDK of Quakey hardware wallet to MetaMask & other software wallets

### 2. True random number test

- [x] Run NIST SP 800-22 randomness testsuit (https://github.com/terrillmoore/NIST-Statistical-Test-Suite)

- [ ] SDK for true random number test based on NIST SP 800-22

### 3. Proof-of-randomness

- [ ] Synchronizing random number's Hash from nodes

- [ ] Run SHA-256 to the summition (second Hash)

- [ ] Comparing the sencond Hash to every Hash form nodes and choose the most close one

### 4. Block verification

- [ ] Verify the Hash and random number form the selected node (or several nodes)

- [ ] Record all transactions and complete the block

### 5. God-Plays-Dices front end
   
- [x] Show the digital signature from QuaKey hardware wallet

- [ ] Show the results of true random number test

- [ ] Show the steps of proof-of-randomness protocol

- [ ] Show the results of block verification and transactions

**So let's build a true fair Internet!**
