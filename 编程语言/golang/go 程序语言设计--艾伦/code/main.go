package main

import (
	"fmt"
)

func main() {

	a := [3]int{1, 2, 3}
	b := [3]int{1, 2, 3}
	// c := 1
	fmt.Println(a == b)
	fmt.Printf("%p,%p", &a, &b)
}
