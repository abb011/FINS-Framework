/*
 * ICMP.h
 *
 *  Created on: Jul 21, 2010
 *      Author: alex
 */

#ifndef ICMP_H_
#define ICMP_H_

/*Type value for an ICMP Error message*/

#define ERROR_UNREACHABLE 	3			/* the destination is unreachable */
#define ERROR_QUENCH 		4			/* source quench (received too many packets) */
#define ERROR_TIME 			11			/* Time to Live reached 0 before reaching destination */
#define ERROR_PARAM 		12			/* Ambiguous or missing value in any field in the datagram */
#define ERROR_REDIRECT 		5			/* When host sends the data to the wrong router. Results in a routing table update for the host */

/* Type value for ICMP Query messages */
#define QUERY_ECHO_REQUEST				0			/* request for echo */
#define QUERY_ECHO_REPLY				8			/* reply to echo*/
#define QUERY_TIMESTAMP_REQUEST			13			/* time stamp request  determines roundtrip of an IP packet */
#define QUERY_TIMESTAMP_REPLY			14			/* time stamp reply */
#define QUERY_ADDR_REQUEST				17			/* request to router on LAN if known address or broadcast to all for the address mask*/
#define	QUERY_ADDR_REPLY				18			/* reply with address mask */
#define	QUERY_ROUTER_REQUEST			10			/* request for router address and if its alive. Multicast / Broadcast */
#define	QUERY_ROUTER_REPLY				9			/* reply with address and if its alive*/

/* code values for destination unreachable */
#define NETWORK_UNR						0			/* The datagram could not reach the specified network */
#define HOST_UNR						1			/* The datagram could not reach the specified host inside of the network*/
#define PROTOCOL_UNR					2			/* Unreachable or invalid protocol number of the host */
#define PORT_UNR						3			/* Invalid port*/
#define FRAGMENTATION_NEEDED			4			/* The packet is of size that needs to be fragmented but the "Do Not Fragment" flag is set*/
#define	SOURCE_ROUTE_FAILED				5			/* Router could not forward the datagram to the next step */
#define	DEST_NETWORK_UNK				6			/* Destination Network Unknown is not used, code 0 is used instead */
#define	DEST_HOST_UNK					7			/* The specified host is not known. ie bad address */
#define SRC_HOST_ISOLATED				8			/* Source Host Isolated is no longer used */
#define	DST_NTWRK_PROHIB				9			/* The source device is not allowed to send data to the network of the destination */
#define	DST_HOST_PROHIB					10			/* The source is allowed to send to the network of the target device, but not to the target device */
#define	DST_NTWRK_SRVC_UNR				11			/* The network specified in the IP address cannot be reached because the service specified in the "Type Of Service" field is unreachable */
#define DST_HOST_SRC_UNR				12			/* The destination specified in the IP address cannot be reached because the service specified in the "Type Of Service" field is unreachable */
#define	COMMUNICATION_PROHIB			13			/* The datagram could not be forwarded due to filtering that blocks messages based on their contents */
#define HOST_PRECED_VIOLATION			14			/* Sent by first-hop router when the precedence value in the "Type of Service" field is not allowed */
#define PRECED_CUTOFF					15			/* Sent by router when the precedence value is lower than the minimum allowed on the network at that point in time */


/* Time exceeded code Values */
#define EXPIRATION  					0			/* The time to live of field has expired*/
#define REASSEMBLY						1			/* The fragment reassembly time has been exceeded */


/* Redirect Code values code 0 and 2 were prohibited by RFC 1812.*/
#define REDIR_NETWORK					0			/* [obsolete] Redirect all future datagrams sent on this network to this device  */
#define REDIR_HOST						1			/* Redirect all future datagrams going to the device/address that caused the ICMP error */
#define REDIR_TOS_NTWRK					2			/*  [obsolete] Forward all future datagrams with the same Type of Service value on the entire network */
#define REDIR_TOS_HOST					3			/* Redirect all future datagrams with the same Type of Service */

#define UNUSED							0			/* The code field is not used by Source Quench*/

struct ip4_header{

	uint8_t ip_verlen;				 	/* IP version & header length (in longs)*/
	uint8_t ip_dif; 					/* differentiated service			*/
	uint16_t ip_len; 					/* total packet length (in octets)	*/
	uint16_t ip_id; 					/* datagram id				*/
	uint16_t ip_fragoff; 				/* fragment offset (in 8-octet's)	*/
	uint8_t ip_ttl; 					/* time to live, in gateway hops	*/
	uint8_t ip_proto; 					/* IP protocol */
	uint16_t ip_cksum; 					/* header checksum 			*/
	uint32_t ip_src; 					/* IP address of source			*/
	uint32_t ip_dst; 					/* IP address of destination		*/
};


/* used by Destination Unreachable, Source Quench, Time Exceeded*/
struct error_message{
	uint32_t unused;					/* 4 bytes of unused data */
	struct ip4_header;					/* original IP header of the original IP datagram */
	unsigned char data[8];				/* Essentially the UDP and TCP headers. Or at least the important parts*/

};
/* used by parameter problems */
struct error_param{
		uint8_t pointer;					/* pointer to the byte that caused the Parameter Problem message to be generated */
		uint24_t unused;					/* 3 bytes of unused data*/
		struct ip4_header;					/* original IP header of the original IP datagram */
		unsigned char data[8];
};


struct query_message{

};

struct icmp_packet{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	union{
		struct error_message;
		struct query_message;
		struct error_param;
	};

};


#endif
