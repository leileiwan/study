package main

import (
	"fmt"
	"os"
)


func main() {
	var res string
	for i:=0;i<len(os.Args);i++{
		res+=os.Args[i]
	}
	fmt.Println(res)
	fmt.Println("zzz")
	
	
}


