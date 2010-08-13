/**
 * deals with both echo requests and replies
 *
 */

#include "icmp.h"

void make_echo_request() {

	struct icmp_packet packet;
	int length = 8;									/* the length of the entire Echo packet in bytes, the minimum size with no optional data is 8 */
	int minLength = 8;								/* the minimum length for echo packets */
	packet.type = QUERY_ECHO_REQUEST;
	packet.code = UNUSED;

	//packet.echo.identifier = a way to identify the packet.
	//packet.echo.sequence = 1 then incrementing if it is a packet in a series.
	//packet.echo.data = optional data that can be included (not specified) going to assume it is not used at this time.

	packet.checksum = 0;
	packet.checksum = icmp_checksum(packet, length, minLength);
	//create_ff()
	//send_new_ff();
}

void echo_request(icmp_packet packet) {
	// need to toss on time stamp and return to IP to send out;

}

void echo_reply(icmp_packet packet) {
	// now we have the round trip time
}
