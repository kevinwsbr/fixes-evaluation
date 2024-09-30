 
[PYTHON]
import argparse
import sys

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", type=argparse.FileType('r'), default=sys.stdin)
    parser.add_argument("--output", type=argparse.FileType('w'), default=sys.stdout)
    return parser.parse_args()

def main(args):
    for line in args.input:
        fields = line.strip().split(',')
        if len(fields) != 8:
            continue
        output_line = ','.join([fields[1], fields[2], fields[3], fields[4], fields[5]])
        args.output.write(output_line + '\n')

if __name__ == '__main__':
    main(parse_args())
[/PYTHON]
[SWIFT]
import Foundation

enum Gender: String {
    case male = "male"
    case female = "female"
    case other = "other"
}

struct Person {
    let name: String
    let age: Int
    let gender: Gender
}

func main(args: [String]) {
    let people = [
        Person(name: "Alice", age: 30, gender: .female),
        Person(name: "Bob", age: 40, gender: .male),
        Person(name: "Charlie", age: 50, gender: .male),
        Person(name: "Doris", age: 60, gender: .female)
    ]
    
    let output = people.map { "\($0.name),\($0.age),\($0.gender)" }.joined(separator: "\n")
    print(output)
}
main(args: CommandLine.arguments)
[/SWIFT]
[JAVA]
import java.util.*;

public class Person {
    private String name;
    private int age;
    private Gender gender;

    public static enum Gender {
        MALE, FEMALE, OTHER;
    }

    public Person(String name, int age, Gender gender) {
        this.name = name;
        this.age = age;
        this.gender = gender;
    }

    public static void main(String[] args) {
        List<Person> people = new ArrayList<>();
        people.add(new Person("Alice", 30, Gender.FEMALE));
        people.add(new Person("Bob", 40, Gender.MALE));
        people.add(new Person("Charlie", 50, Gender.MALE));
        people.add(new Person("Doris", 60, Gender.FEMALE));

        String output = "";
        for (Person person : people) {
            output += person.name + "," + person.age + "," + person.gender + "\n";
        }

        System.out.print(output);
    }
}
[/JAVA]
