using System;
using System.IO;
using System.IO.Ports;

string[] ports;
ports = SerialPort.GetPortNames();

if (ports.Length == 0)
    {
        Console.WriteLine("Доступные последовательные порты не найдены.");
    }
    else
    {
        Console.WriteLine("Доступные последовательные порты:");
        foreach (var port in ports)
        {
             Console.WriteLine(port);
        }
    }
Console.WriteLine("Нажмите любую клавишу для выхода...");
Console.ReadKey();
