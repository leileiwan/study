package main

import "fmt"

func main() {
	var a map[string]int
	delete(a, "alice")
	fmt.Printf("v%", a)
}
