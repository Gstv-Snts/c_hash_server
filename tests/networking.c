#include "networking.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "unity.h"

void setUpTCP() {};
void tearDownTCP() {};

void test_tcp() {
  setUpTCP();

  struct sockaddr_in addr = create_server_address(1337);
  TEST_ASSERT_EQUAL(addr.sin_family, 2);
  TEST_ASSERT_EQUAL(addr.sin_port, htons(1337));
  TEST_ASSERT_EQUAL(addr.sin_addr.s_addr, htonl(0));

  tearDownTCP();
}
