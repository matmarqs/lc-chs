package main

import (
	"fmt"
)

func main() {
	var A float64
	var B float64

	fmt.Scan(&A)
	fmt.Scan(&B)

	fmt.Printf("MEDIA = %.5f\n", (3.5*A+7.5*B)/11.0)
}
