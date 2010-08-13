
#include "icmp.h"

void icmp_switch(struct finsFrame* ff) {

	struct icmp_packet packet;
	memcpy(&packet, ff->dataFrame.pdu, ff->dataFrame.pduLength);

	switch (packet.type) {
	case 0:
		// echo request
		break;
	case 3:
		// Error Unreachable
		break;
	case 4:
		// Error Source Quench
		break;
	case 5:
		// Error Redirect
		break;
	case 8:
		// Query Echo Reply
		break;
	case 9:
		// Query Router Reply
		break;
	case 10:
		// Router Request
		break;
	case 11:
		// Error Time to Live exceeded
		break;
	case 12:
		// Error Paramater Problem
		break;
	case 13:
		// Query Timestamp Request
		break;
	case 14:
		// Query Timestamp Reply
		break;
	case 17:
		// Query address request
		break;
	case 18:
		// Query address reply
		break;
	default:
		puts(" Invalid Type Value for the ICMP packet");
		break;
	}

}
