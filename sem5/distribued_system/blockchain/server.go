/*
 * Author : Lambert Luc
 * Description : Node algorithm in a blockchain managemment system
 */

package main

import (
	"bufio"
	"bytes"
	"context"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net"
	"os"
	"strconv"
	"strings"
	"time"

	"cloud.google.com/go/storage"
	"google.golang.org/api/iterator"
	"gopkg.in/yaml.v2"
)

type Node struct {
	id      int
	address string
}

type Current_Node struct {
	me         Node
	neighbours []Node
	d          *net.Dialer
}

type Transaction struct {
	id       int
	sender   string
	receiver string
	amount   float64
}

type node_describe_yaml struct {
	ID         int    `yaml:"id"`
	Address    string `yaml:"address"`
	Neighbours []struct {
		ID      int    `yaml:"id"`
		Address string `yaml:"address"`
	} `yaml:"neighbours"`
}

type msg struct {
	function             string
	id                   int
	number_of_good_node  int
	total_number_of_node int
	sender               string
	receiver             string
	amount               float64
}

const PROJECT_ID = "distribued-system-blockchain"
const CLIENT_ADDR = "127.0.0.10"

// createBucketClassLocation creates a new bucket in the project with Storage class and
// location.
func createBucketClassLocation(projectID string, bucketName string) error {

	ctx := context.Background()
	client, err := storage.NewClient(ctx)
	if err != nil {
		return fmt.Errorf("storage.NewClient: %v", err)
	}
	defer client.Close()

	ctx, cancel := context.WithTimeout(ctx, time.Second*30)
	defer cancel()

	storageClassAndLocation := &storage.BucketAttrs{
		StorageClass: "STANDARD",
		Location:     "EUROPE-WEST6",
	}
	bucket := client.Bucket(bucketName)
	if err := bucket.Create(ctx, projectID, storageClassAndLocation); err != nil {
		return fmt.Errorf("Bucket(%q).Create: %v", bucketName, err)
	}
	fmt.Printf("Created bucket %v in %v with storage class %v\n", bucketName, storageClassAndLocation.Location, storageClassAndLocation.StorageClass)
	return nil
}

// listBuckets lists buckets in the project.
func listBuckets(projectID string) ([]string, error) {
	// projectID := "my-project-id"
	ctx := context.Background()
	client, err := storage.NewClient(ctx)
	if err != nil {
		return nil, fmt.Errorf("storage.NewClient: %v", err)
	}
	defer client.Close()

	ctx, cancel := context.WithTimeout(ctx, time.Second*30)
	defer cancel()

	var buckets []string
	it := client.Buckets(ctx, projectID)
	for {
		battrs, err := it.Next()
		if err == iterator.Done {
			break
		}
		if err != nil {
			return nil, err
		}
		buckets = append(buckets, battrs.Name)
	}
	return buckets, nil
}

func bucketExist(bucket string) bool {
	buckets, err := listBuckets(PROJECT_ID)
	if err != nil {
		fmt.Printf("%s\n", err)
		return false
	}

	for _, b := range buckets {
		if b == bucket {
			return true
		}
	}
	return false
}

func uploadTransaction(bucket string, t Transaction) error {
	s := fmt.Sprintf("Transaction %d", t.id)
	fmt.Printf("%s\n", s)
	return streamFileUpload(bucket, s, t)
}

func streamFileUpload(bucket string, object string, t Transaction) error {
	ctx := context.Background()
	client, err := storage.NewClient(ctx)
	if err != nil {
		return fmt.Errorf("storage.NewClient: %v", err)
	}
	defer client.Close()

	t_str := fmt.Sprintf("%d %s %s %f", t.id, t.sender, t.receiver, t.amount)
	fmt.Println(t_str)
	b := []byte(t_str)

	buf := bytes.NewBuffer(b)

	ctx, cancel := context.WithTimeout(ctx, time.Second*50)
	defer cancel()

	// Upload an object with storage.Writer.
	wc := client.Bucket(bucket).Object(object).NewWriter(ctx)
	wc.ChunkSize = 0 // note retries are not supported for chunk size 0.

	if _, err = io.Copy(wc, buf); err != nil {
		return fmt.Errorf("io.Copy: %v", err)
	}
	// Data can continue to be added to the file until the writer is closed.
	if err := wc.Close(); err != nil {
		return fmt.Errorf("Writer.Close: %v", err)
	}
	fmt.Printf("%v uploaded to %v.\n", object, bucket)

	return nil
}

// downloadFileIntoMemory downloads an object.
func downloadFileIntoMemory(bucket string, object string) ([]byte, error) {

	ctx := context.Background()
	client, err := storage.NewClient(ctx)
	if err != nil {
		return nil, fmt.Errorf("storage.NewClient: %v", err)
	}
	defer client.Close()

	ctx, cancel := context.WithTimeout(ctx, time.Second*50)
	defer cancel()

	rc, err := client.Bucket(bucket).Object(object).NewReader(ctx)
	if err != nil {
		return nil, fmt.Errorf("Object(%q).NewReader: %v", object, err)
	}
	defer rc.Close()

	data, err := ioutil.ReadAll(rc)
	if err != nil {
		return nil, fmt.Errorf("ioutil.ReadAll: %v", err)
	}
	fmt.Printf("Blob %v downloaded.\n", object)
	return data, nil
}

func downloadTransaction(bucket string, idTransaction int) (Transaction, error) {
	data, err := downloadFileIntoMemory(bucket, fmt.Sprintf("Transaction %d", idTransaction))

	if err != nil {
		var t Transaction
		return t, fmt.Errorf("%v\n", err)
	}

	transaction_str := strings.Split(string(data), " ")

	var t Transaction

	t.id, err = strconv.Atoi(transaction_str[0])

	if err != nil {
		var t Transaction
		return t, fmt.Errorf("%v\n", err)
	}

	t.sender = transaction_str[1]
	t.receiver = transaction_str[2]
	t.amount, err = strconv.ParseFloat(transaction_str[3], 64)

	if err != nil {
		var t Transaction
		return t, fmt.Errorf("%v\n", err)
	}

	return t, nil
}

// deleteFile removes specified object.
func deleteFile(bucket, object string) error {
	ctx := context.Background()
	client, err := storage.NewClient(ctx)
	if err != nil {
		return fmt.Errorf("storage.NewClient: %v", err)
	}
	defer client.Close()

	ctx, cancel := context.WithTimeout(ctx, time.Second*10)
	defer cancel()

	o := client.Bucket(bucket).Object(object)

	// Optional: set a generation-match precondition to avoid potential race
	// conditions and data corruptions. The request to upload is aborted if the
	// object's generation number does not match your precondition.
	attrs, err := o.Attrs(ctx)
	if err != nil {
		return fmt.Errorf("object.Attrs: %v", err)
	}
	o = o.If(storage.Conditions{GenerationMatch: attrs.Generation})

	if err := o.Delete(ctx); err != nil {
		return fmt.Errorf("Object(%q).Delete: %v", object, err)
	}
	fmt.Printf("Blob %v deleted.\n", object)
	return nil
}

func parse_yaml(yaml_file string) node_describe_yaml {
	file, err := os.ReadFile(yaml_file)
	if err != nil {
		log.Fatal(err)
	}

	var node_description node_describe_yaml

	err2 := yaml.Unmarshal(file, &node_description)
	if err2 != nil {
		log.Fatal(err2)
	}

	return node_description
}

func init_node(c *Current_Node, yaml_file string) {
	node_description := parse_yaml(yaml_file)
	c.me.address = node_description.Address
	c.me.id = node_description.ID

	for _, neighbour := range node_description.Neighbours {
		var temp_node Node
		temp_node.address = neighbour.Address
		temp_node.id = neighbour.ID
		c.neighbours = append(c.neighbours, temp_node)
	}
	//create specific Dialer to recognize node
	c.d = &net.Dialer{
		LocalAddr: &net.TCPAddr{
			IP:   net.ParseIP(c.me.address),
			Port: 0,
		},
	}
}

func print_current_node(c Current_Node) {
	fmt.Printf("Node %d address %s : \n", c.me.id, c.me.address)
	for _, neighbour := range c.neighbours {
		fmt.Printf("	Neighbour %d address %s\n", neighbour.id, neighbour.address)
	}
	fmt.Printf("\n")
}

func get_socket(n Node) string {
	return fmt.Sprintf("%s:%d", n.address, n.id+30000)
}

func parse_msg(m *msg, data_receive string) {
	separator := " "
	data := strings.Split(data_receive, separator)
	if len(data) != 8 {
		log.Fatal("message received does not fit msg struct")
	}
	m.function = data[0]
	m.id, _ = strconv.Atoi(data[1])
	m.number_of_good_node, _ = strconv.Atoi(data[2])
	m.total_number_of_node, _ = strconv.Atoi(data[3])
	m.sender = data[4]
	m.receiver = data[5]
	m.amount, _ = strconv.ParseFloat(data[6], 64)
	// data[7] = "\n" -> delimeter for Reading operation
}

func init_trans(t *Transaction, id int, sender string, receiver string, amount float64) {
	t.id = id
	t.sender = sender
	t.receiver = receiver
	t.amount = amount
}

func (t *Transaction) String() string {
	return fmt.Sprintf("%s receive %f from %s id:%d", t.receiver, t.amount, t.sender, t.id)
}

func print_transaction(transactions []Transaction) {
	for _, value := range transactions {
		fmt.Println(value.String())
	}
}

func (m msg) String() string {
	return fmt.Sprintf("%s %d %d %d %s %s %f \n", m.function, m.id, m.number_of_good_node,
		m.total_number_of_node, m.sender, m.receiver, m.amount)
}

func send_msg(d *net.Dialer, m msg, socket string) {
	conn, err := d.Dial("tcp", socket)

	if err != nil {
		log.Fatal(err)
	}

	conn.Write([]byte(m.String()))

	conn.Close()
}

func receive_msg(m *msg, ln net.Listener) string {

	fmt.Printf("Waiting Conn... \n")
	// accept connection
	conn, _ := ln.Accept()

	fmt.Printf("Ok %s Connected\n", conn.RemoteAddr().String())
	// get message, output
	message, err := bufio.NewReader(conn).ReadString('\n')

	if err != nil {
		log.Fatal(err)
	}

	parse_msg(m, message)

	from := conn.RemoteAddr().String()

	conn.Close()
	fmt.Printf("Received first msg \n")
	return from
}

func init_msg(m *msg, function string, id int, number_of_good_node int,
	total_number_of_node int, sender string, receiver string, amount float64) {
	m.function = function
	m.id = id
	m.number_of_good_node = number_of_good_node
	m.total_number_of_node = total_number_of_node
	m.sender = sender
	m.receiver = receiver
	m.amount = amount
}

// broad cast wave algorithm
func create_transaction(t *Transaction, c Current_Node, Is_first_node bool, ln net.Listener) {

	var m msg
	init_msg(&m, "create", t.id, 0, 0, t.sender, t.receiver, t.amount)

	bucket_name := "bucket_node_" + strconv.Itoa(c.me.id)
	if !bucketExist(bucket_name) {
		createBucketClassLocation(PROJECT_ID, bucket_name)
	}

	uploadTransaction(bucket_name, *t)

	count := 1
	if Is_first_node {
		count = 0
	}

	for _, neighbour := range c.neighbours {
		go send_msg(c.d, m, get_socket(neighbour))
	}

	for count < len(c.neighbours) {
		//   - Receive a message D
		conn, _ := ln.Accept()
		fmt.Printf("Received from %s\n", conn.RemoteAddr().String())
		count++
	}
}

func verify_identical_transaction(t Transaction, t2 Transaction) bool {
	return (t.id == t2.id && t.amount == t2.amount && t.receiver == t2.receiver && t.sender == t2.sender)
}

func vote(t *Transaction, number_of_good_node int, total_number_of_node int, c Current_Node, Is_first_node bool, ln net.Listener, parent Node) {

	var m msg
	ngn := 0
	tnn := 0

	init_msg(&m, "vote", t.id, number_of_good_node, total_number_of_node, t.sender, t.receiver, t.amount)

	count := 1

	if Is_first_node {
		parent.address = "0:0:0:1"
		for _, neighbour := range c.neighbours {
			go send_msg(c.d, m, get_socket(neighbour))
		}
		count = 0
	} else {
		fmt.Printf("Parent is %s\n", get_socket(parent))

		for _, neighbour := range c.neighbours {
			if parent.address != neighbour.address {
				go send_msg(c.d, m, get_socket(neighbour))
			}
		}
	}

	for count < len(c.neighbours) {

		conn, _ := ln.Accept()
		count++
		fmt.Printf("Received from %s\n", conn.RemoteAddr().String())
		message, err := bufio.NewReader(conn).ReadString('\n')

		if err != nil {
			log.Fatal(err)
		}

		parse_msg(&m, message)

		ngn += m.number_of_good_node
		tnn += m.total_number_of_node
	}

	if count == len(c.neighbours) {
		bucket_name := "bucket_node_" + strconv.Itoa(c.me.id)
		bucket_t, err := downloadTransaction(bucket_name, t.id)

		if err != nil {
			fmt.Print(err)
		}

		if verify_identical_transaction(*t, bucket_t) {
			ngn++
		}
		tnn++

		if parent.address != "0:0:0:1" {
			fmt.Printf("sending to parent %s, %d good node, %d total node\n", get_socket(parent), ngn, tnn)
			m.number_of_good_node = ngn
			m.total_number_of_node = tnn
			send_msg(c.d, m, get_socket(parent))
		} else {
			res := (float64(ngn) * 100.0 / float64(tnn))
			fmt.Printf("number of good node = %d, total node = %d, rate = %v%% \n", ngn, tnn, res)
		}
	}
}

func fake(authentic *Transaction, fake *Transaction) {
	authentic.id = fake.id
	authentic.sender = fake.sender
	authentic.receiver = fake.receiver
	authentic.amount = fake.amount
}

// listFiles lists objects within specified bucket.
func listFiles(bucket string) error {
	// bucket := "bucket-name"
	ctx := context.Background()
	client, err := storage.NewClient(ctx)
	if err != nil {
		return fmt.Errorf("storage.NewClient: %v", err)
	}
	defer client.Close()

	ctx, cancel := context.WithTimeout(ctx, time.Second*10)
	defer cancel()

	it := client.Bucket(bucket).Objects(ctx, nil)
	for {
		attrs, err := it.Next()
		if err == iterator.Done {
			break
		}
		if err != nil {
			return fmt.Errorf("Bucket(%q).Objects: %v", bucket, err)
		}
		fmt.Println(attrs.Name)
	}
	return nil
}

func list_of_trans(c Current_Node) {
	err := listFiles("bucket_node_" + strconv.Itoa(c.me.id))
	if err != nil {
		fmt.Print(err)
	}
}

// Main function
func main() {
	if len(os.Args) < 2 || len(os.Args) > 3 {
		fmt.Println("Usage :\r\n\t go run node.go neighbour-[x].yaml (list/fake)")
	} else if len(os.Args) == 3 {
		var c Current_Node
		init_node(&c, os.Args[1])
		switch os.Args[2] {
		case "list":
			list_of_trans(c)
			break
		case "fake":
			var fake_t Transaction
			fake_t.amount = -0.00
			fake_t.id = 1
			fake_t.receiver = "FAKE"
			fake_t.sender = "FAKE"
			bucket_name := "bucket_node_" + strconv.Itoa(c.me.id)
			err := deleteFile(bucket_name, "Transaction 1")
			if err != nil {
				fmt.Print(err)
			}
			uploadTransaction(bucket_name, fake_t)
			break
		}
		os.Exit(0)
	} else if len(os.Args) == 2 {
		//do

		//init node
		var c Current_Node
		init_node(&c, os.Args[1])
		print_current_node(c)

		// listen on port randomly choose, address of node
		server := fmt.Sprintf("%s:%d", c.me.address, 30000+c.me.id)
		ln, _ := net.Listen("tcp", server)
		fmt.Printf("Start server listening on %s\n", ln.Addr().String())

		for {
			var m msg
			socket_str := receive_msg(&m, ln)

			Is_first_node := false
			socket := strings.Split(socket_str, ":")
			addr_ip := socket[0]

			if addr_ip == CLIENT_ADDR {
				Is_first_node = true
			}

			var t Transaction
			init_trans(&t, m.id, m.sender, m.receiver, m.amount)

			switch m.function {
			case "create":
				create_transaction(&t, c, Is_first_node, ln)

				break
			case "vote":
				var parent Node
				parent.address = addr_ip
				parent.id, _ = strconv.Atoi(strings.Split(parent.address, ".")[3])

				vote(&t, m.number_of_good_node, m.total_number_of_node, c, Is_first_node, ln, parent)
				break
			}
			fmt.Printf("Node job done \n")
		}
	}
}
