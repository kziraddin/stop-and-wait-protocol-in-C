
/* mplementing a reliable transport protocol involves several key steps. Here are some general guidelines that you can follow:

-> Define the protocol: You need to define the protocol in terms of what it does and how it works. 
This should include information about how packets are transmitted, how errors are handled, 
and how acknowledgments are sent and received.

-> Establish a connection: You need to establish a connection between the two endpoints that will be communicating 
using the protocol. This may involve a three-way handshake, where the endpoints exchange messages to synchronize their communication.

-> Packetization: Divide the data to be transmitted into smaller packets, if needed. This is especially important 
if the data is too large to be transmitted in a single packet.

-> Add headers: Each packet should contain a header that includes information such as the source and destination addresses, 
the packet number, and any other relevant metadata.

-> Send the packets: The sender should send the packets over the network to the receiver.

->Receive the packets: The receiver should receive the packets and check them for errors. If a packet is damaged or lost, 
the receiver should request that the sender retransmit the packet.

-> Acknowledge receipt: Once the receiver has received a packet, it should send an acknowledgment message to the sender 
to confirm that it has been received.

-> Retransmit packets: If the sender does not receive an acknowledgment message from the receiver within a certain amount of time, 
it should retransmit the packet.

->Close the connection: When all the packets have been transmitted and received, the connection should be closed to free up resources.

-> Handle errors: Finally, the protocol should include error handling mechanisms to ensure that errors are detected and 
corrected in a timely manner.
*/


/* STOP AND WAIT PROTOCOL (Alternating-Bit-Protocol) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define PACKET_SIZE 20
#define TIMEOUT_SEC 3

typedef struct Packet {
    int seq_num;
    bool is_ack;
    char data[PACKET_SIZE];
} Packet;

void send_packet(Packet packet) {
    printf("Sending packet with sequence number %d...\n", packet.seq_num);
    // Simulate transmission delay
    sleep(1);
}

Packet receive_packet() {
    Packet packet;
    // Simulate packet loss
    if (rand() % 10 > 2) {
        printf("Packet lost!\n");
        packet.seq_num = -1;
    } else {
        printf("Packet received!\n");
        packet.seq_num = rand() % 2;  //returns 0 or 1
        packet.is_ack = true;  
        sprintf(packet.data, "ACK%d", packet.seq_num); //If successful, it returns the total number of characters written excluding null-character appended in the string, in case of failure a negative number is returned.
    }
    // Simulate transmission delay
    sleep(1);
    return packet;
}

int main() {
    srand(time(NULL));
    Packet packet_to_send;
    Packet received_packet;
    bool waiting_for_ack = false;
    int next_seq_num = 0;
    while (true) {
        if (!waiting_for_ack) {
            // Generate packet to send
            packet_to_send.seq_num = next_seq_num;
            packet_to_send.is_ack = false;
            sprintf(packet_to_send.data, "Packet %d", next_seq_num);
            // Send packet
            send_packet(packet_to_send);
            // Set waiting_for_ack to true and start timeout timer
            waiting_for_ack = true;
            time_t start_time = time(NULL);
            while (difftime(time(NULL), start_time) < TIMEOUT_SEC) {
                // Check for incoming packet
                received_packet = receive_packet();
                if (received_packet.seq_num == next_seq_num && received_packet.is_ack) {
                    printf("ACK received for packet %d\n", next_seq_num);
                    waiting_for_ack = false;
                    next_seq_num = (next_seq_num + 1) % 2;
                    break;
                }
            }
            if (waiting_for_ack) {
                // Timeout occurred
                printf("Timeout occurred for packet %d\n", next_seq_num);
            }
        } else {
            // Check for incoming packet
            received_packet = receive_packet();
            if (received_packet.seq_num == next_seq_num && received_packet.is_ack) {
                printf("ACK received for packet %d\n", next_seq_num);
                waiting_for_ack = false;
                next_seq_num = (next_seq_num + 1) % 2;
            }
        }
    }
    return 0;
}

