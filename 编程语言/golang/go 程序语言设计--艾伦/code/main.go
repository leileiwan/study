package main

import (
	"fmt"
)

func main() {

	a := [3]int{1, 2, 3}
	b := [3]int{1, 2, 3}
	fmt.Println(a == b)
	fmt.Println(a, b)
}
