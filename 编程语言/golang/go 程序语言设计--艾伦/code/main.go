package main

import (
	"fmt"
	"os"
)

func main() {
	var res string
	for _, tem := range os.Args[1:] {
		res = res + " " + tem
	}
	fmt.Println(res)
}
