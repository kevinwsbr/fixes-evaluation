[PYTHON]
from ctypes import *
import sys

class PRINTER_INFO_1(Structure):
    _fields_ = [("flags", c_short),
                ("priority", c_short),
                ("default_priority", c_short),
                ("local_printer", c_char_p),
                ("network_printer", c_char_p),
                ("driver_name", c_char_p),
                ("comment", c_char_p)]

def get_printer_info_1():
    p = PRINTER_INFO_1()
    p.flags = 0
    p.priority = 0
    p.default_priority = 0
    p.local_printer = b"\\x7fOnboardPrinter"
    p.network_printer = b"\\x7fNetworkPrinter"
    p.driver_name = b"\\x7fSampleDriver"
    p.comment = b"This is a test comment."
    return p

if __name__ == "__main__":
    print(get_printer_info_1())
[/PYTHON]
[JAVA]
import java.io.*;

public class Spoolss {
    public static void main(String[] args) throws IOException {
        String printerName = "\\x7fOnboardPrinter";
        String printerDriver = "\\x7fSampleDriver";
        String comment = "This is a test comment.";

        // PRINTER_INFO_1
        int flags = 0;
        short priority = 0;
        short defaultPriority = 0;

        System.out.println("PRINTER_INFO_1");
        System.out.println("flags: " + flags);
        System.out.println("priority: " + priority);
        System.out.println("defaultPriority: " + defaultPriority);
        System.out.println("localPrinter: " + printerName);
        System.out.println("networkPrinter: " + printerDriver);
        System.out.println("driverName: " + comment);
        System.out.println();
    }
}
[/JAVA]
[C++]
int main()
{
	// PRINTER_INFO_1
	short flags = 0;
	short priority = 0;
	short defaultPriority = 0;

	std::string printerName = "\\x7fOnboardPrinter";
	std::string printerDriver = "\\x7fSampleDriver";
	std::string comment = "This is a test comment.";

	printf("PRINTER_INFO_1\n");
	printf("\tflags: %d\n", flags);
	printf("\tpriority: %d\n", priority);
	printf("\tdefaultPriority: %d\n", defaultPriority);
	printf("\tlocalPrinter: %s\n", printerName.c_str());
	printf("\tnetworkPrinter: %s\n", printerDriver.c_str());
	printf("\tdriverName: %s\n", comment.c_str());

	return 0;
}
[/C++]
[PHP]
<?php
class Spoolss
{
    public function printPrinterInfo1()
    {
        $flags = 0;
        $priority = 0;
        $defaultPriority = 0;
        $printerName = "\\x7fOnboardPrinter";
        $printerDriver = "\\x7fSampleDriver";
        $comment = "This is a test comment.";

        print("PRINTER_INFO_1");
        print("\tflags: $flags");
        print("\tpriority: $priority");
        print("\tdefaultPriority: $defaultPriority");
        print("\tlocalPrinter: $printerName");
        print("\tnetworkPrinter: $printerDriver");
        print("\tdriverName: $comment");
        print("\n");
    }
}
?>
[/PHP]
[TYPESCRIPT]
import * as Rx from 'rxjs';
import { map, scan, switchMap } from 'rxjs/operators';

interface PrinterInfo1 {
    flags: number;
    priority: number;
    defaultPriority: number;
    localPrinter: string;
    networkPrinter: string;
    driverName: string;
}

class Spoolss {
    printPrinterInfo1(): Rx.Observable<PrinterInfo1> {
        const flags = 0;
        const priority = 0;
        const defaultPriority = 0;
        const printerName = "\\x7fOnboardPrinter";
        const printerDriver = "\\x7fSampleDriver";
        const comment = "This is a test comment.";

        return Rx.Observable.of<PrinterInfo1>({
            flags,
            priority,
            defaultPriority,
            localPrinter: printerName,
            networkPrinter: printerDriver,
            driverName: comment
        });
    }
}
[/TYPESCRIPT]
[JAVASCRIPT]
const { Observable } = require('rxjs');

class Spoolss {
    printPrinterInfo1() {
        const flags = 0;
        const priority = 0;
        const defaultPriority = 0;
        const printerName = "\\x7fOnboardPrinter";
        const printerDriver = "\\x7fSampleDriver";
        const comment = "This is a test comment.";

        return Observable.of({
            flags,
            priority,
            defaultPriority,
            localPrinter: printerName,
            networkPrinter: printerDriver,
            driverName: comment
        });
    }
}
[/JAVASCRIPT]
[SCALA]
case class PrinterInfo1(flags: Short, priority: Short, defaultPriority: Short, localPrinter: String, networkPrinter: String, driverName: String)

object Spoolss {
  def printPrinterInfo1() = {
    val flags = 0.toShort
    val priority = 0.toShort
    val defaultPriority = 0.toShort
    val printerName = "\\x7fOnboardPrinter"
    val printerDriver = "\\x7fSampleDriver"
    val comment = "This is a test comment."

    PrinterInfo1(flags, priority, defaultPriority, printerName, printerDriver, comment)
  }
}
[/SCALA]
[CSHARP]
using System;

namespace Spoolss
{
    class Program
    {
        static void Main(string[] args)
        {
            short flags = 0;
            short priority = 0;
            short defaultPriority = 0;
            string printerName = "\\x7fOnboardPrinter";
            string printerDriver = "\\x7fSampleDriver";
            string comment = "This is a test comment.";

            Console.WriteLine("PRINTER_INFO_1");
            Console.WriteLine($"\tflags: {flags}");
            Console.WriteLine($"\tpriority: {priority}");
            Console.WriteLine($"\tdefaultPriority: {defaultPriority}");
            Console.WriteLine($"\tlocalPrinter: {printerName}");
            Console.WriteLine($"\tnetworkPrinter: {printerDriver}");
            Console.WriteLine($"\tdriverName: {comment}");
        }
    }
}
[/CSHARP]
