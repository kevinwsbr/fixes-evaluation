 
[PYTHON]
import argparse

class Person:
    def __init__(self, name):
        self.name = name

def main():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('--reversed', action='store_true', help='reverse the input numbers')
    parser.add_argument('numbers', metavar='N', type=int, nargs='+', help='numbers to process')
    args = parser.parse_args()

    if args.reversed:
        print(args.numbers[::-1])
    else:
        print(args.numbers)

if __name__ == '__main__':
    main()
[/PYTHON]
 [SCALA]
import scala.math._

object MyMath {
  def isPrime(n: Int): Boolean = {
    if (n <= 1) return false
    for (i <- 2 until ceil(sqrt(n)).toInt)
      if (n % i == 0) return false
    return true
  }
}
[/SCALA]
 [PERL]
#!/usr/bin/perl
use strict;
use warnings;

my $name = 'Victor';
my @scores = (90, 75, 60, 98, 100, 100);

print "Hello, $name!\n";
print "Your scores are: @scores\n";

if (any { $_ < 50 } @scores) {
  print "You have some failing scores.\n";
}
else {
  print "All your scores are great!\n";
}
[/PERL]
 [PHP]
<?php
class Person {
    private $name;

    public function __construct($name) {
        $this->name = $name;
    }

    public function sayHello() {
        return "Hello, my name is " . $this->name;
    }
}

$person = new Person("John");
echo $person->sayHello();
?>
[/PHP]
