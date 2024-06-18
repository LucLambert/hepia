/*
 * Author : Lambert Luc
 * Description : Test blockchain managemment system
 */

package main

import (
	"fmt"
	"log"
	"net"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage :\r\n\t go run test_network.go [socket]")
	}

	dialer := &net.Dialer{
		LocalAddr: &net.TCPAddr{
			IP:   net.ParseIP("127.0.0.10"),
			Port: 0,
		},
	}
	conn, err := dialer.Dial("tcp", os.Args[1])

	if err != nil {
		log.Fatal(err)
	}

	msg := "vote 1 0 0 Pierre Paul 14.0 \n"
	test := []byte(msg)
	conn.Write(test)

	conn.Close()
}
