package twopow

import "testing"

func TestTwoPow(t *testing.T) {
	cases := []struct {
		n    uint
		want uint64
	}{
		{0, 1},
		{2, 4},
		{10, 1024},
		{63, 9223372036854775808},
	}
	for _, c := range cases {
		got, err := TwoPow(c.n)
		if err != nil {
			t.Fatalf("TwoPow(%d) unexpected error: %v", c.n, err)
		}
		if got != c.want {
			t.Errorf("TwoPow(%d) = %d, want %d", c.n, got, c.want)
		}
	}
}

func TestTwoPowOverflow(t *testing.T) {
	if _, err := TwoPow(64); err == nil {
		t.Fatal("TwoPow(64) expected an error, got nil")
	}
}
