# God-Plays-Dices
The Proof-of-Randomness consensus protocol for blochchains

Einstein once questioned the ture randomness of quantum measurement as "God never play dice". However,  quantum randomness is proved by a huge number of experiments and we now know that "God does play dices". 

Nowdays, small-size quantum random number generator (QRNG) chip is invented and millions of QRNG Chips are integrated into smart phones, e.g. Samsung Galaxy Quantum 1-3. 
We have already developed a quantum USB-key device, called Q-Key. It indeed a blockchain hardare wallet plus a QRNG chip, which runs standard ECC for blockchains while replace all pseudo random numbers by quantum random numbers in ECC.

Some projects using our Q-Key to give digital signature to files, especially AIGC iamges, are listed below

https://github.com/stereoF/artBox (for all systems), 
https://github.com/jiayouww/artBox_Win (only for Windows).

Since QRNG is a physical device, it is not only a soucre of random number substitutions, but also a soucre of ture fairness. This is the realism meaning of "GOD PLAYS DICE". For this reason, we invented a proof-of-randomness (PoR) protocol for blockchain consensus, and released it on arXiv: https://arxiv.org/abs/2211.15417

In blockchains, the proof-of-work (PoW) requires expensive hardwares now and wastes electricity energy a lot, whcih mean only some big nodes with huge computing power could compete the rights of recording new blocks. Altrough the proof-of-stake (PoS) save 99% energy cost, it requiers staking of crypto currency to compete the rights of recording new blocks, while the wining probility of a node is proptional to the amount of crypto currency it has. This makes PoS has super rich nodes and maximum extractable value (MEV) attack usually happen. Therefore, both PoW and PoS do NOT care about fairness now, which betrays the original will of decentralizion. 

PoR could bring true fairness to blockchians. A low cost hardare wallet (Q-Key) is the only required device. Everyone could compete the rights of recording new blocks with one low-cost hardare wallet (Q-Key). It could be a revolution of blockchain fundemetal consensus. 

For the revolution, we have a plan:

1. SDK of Q-Key hardware wallet.
2. SDK for generation and testing of random number test (NIST SP 800-22 randomness testsuit)
3. Synchronizing random number's Hash from nodes,  and run SHA-256 to the summition (second Hash).
4. Comparing the sencond Hash to every Hash form all nodes and choose the most close one. It's indeed a decentralized lottery algorism. 
5. Verify the Hash and random number form the selected node (or several nodes), record all transactions, finish the block.

Let's build a true fair Internet!
