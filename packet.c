/*PACKET*/
struct packet
{
//length of packet
  int len;
//sequence num
  int number;
//max pckset size 1024
  char data[1024];
};
