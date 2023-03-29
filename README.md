# stop-and-wait-protocol-in-C

Overview 

In this laboratory programming assignment, you will be writing the sending and receiving transport-level code 
for implementing a simple reliable data transfer protocol. There are two versions of this lab, 
the Alternating-Bit-Protocol version and the Pipelining version: the Go-Back-N version, and the Selective Repeat version. 
This lab should be fun since your implementation will differ very little from what would be required in a real-world situation. 
For our simulation, we assume that sender is sending the following message cited from a song – “Twinkle, twinkle little star”.  


Twinkle, twinkle little star. 
How I wonder what you are. Up above the world so high. 
Like a diamond in the sky. 
Twinkle, twinkle little star. 
How I wonder what you are. 
Twinkle, twinkle little star. 
How I wonder what you are. Up above the world so high. 
Like a diamond in the sky. 
Twinkle, twinkle little star. 
How I wonder what you are. 

*Each word will be processed into a packet with a sequence number.
  
The routines you will write 
The procedures you will write are for the sending entity (A), ‘Sender’ and the receiving entity (B), ‘Receiver’.  
Only unidirectional transfer of data (from A to B) is required. Of course, the B side will have to send packets 
to A to acknowledge (positively) receipt of data.  
The unit of data passed between sender and receiver is the packet, which is declared as: 

struct pkt { 
   int seqnum;    
   int acknum; 
   char payload[20]; 
}; 

*For simplifying our project, We do not implement Checksum for our data transfer protocols. 



The (Stop-and-Wait) Alternating-Bit-Protocol Version of this lab. You are simulating rdt3.0Protocol:  
channels with errors and loss new assumption: underlying channel can also lose packets (data, ACKs) 
	* checksum, seq. #, ACKs, retransmissions will be of help … but not enough 

approach: sender waits “reasonable” amount of time for ACK  
* retransmits if no ACK received in this time, if pkt (or ACK) just delayed (not lost) 
* retransmission will be duplicate, but seq. #’s already handles this  
* receiver must specify seq # of pkt being ACKed, requires countdown timer 
