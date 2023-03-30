STOP AND WAIT PROTOCOL implementation in C:

The Stop-and-Wait protocol is a simple flow control mechanism used in communication networks, particularly in telecommunications and computer networks. It is a half-duplex protocol that ensures reliable delivery of data by transmitting a data frame and waiting for an acknowledgement (ACK) message from the receiver before transmitting the next frame.

Here is how the Stop-and-Wait protocol works:

The sender sends a frame to the receiver.

The sender waits for an acknowledgement (ACK) message from the receiver.

If the sender does not receive an ACK within a certain time interval, it retransmits the same frame.

If the sender receives an ACK message, it sends the next frame.

The receiver receives the frame and sends an ACK message back to the sender.

If the receiver detects an error in the frame, it discards the frame and sends a negative acknowledgement (NAK) message back to the sender.

If the sender receives a NAK message, it retransmits the same frame.

The process continues until all frames are successfully transmitted and acknowledged.

The Stop-and-Wait protocol is a very simple and reliable protocol, but it has some limitations. One of the main limitations is its low efficiency, as the sender can only transmit one frame at a time and must wait for an ACK before sending the next frame. This protocol is best suited for situations where the data transmission rate is low, and the transmission distance is short.
