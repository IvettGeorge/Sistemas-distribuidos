package pkg1practica;

import java.net.*;
import java.io.*;
import java.util.Scanner;

public class SocketServidor
{    
    public static void main (String [] args)
    {
        new SocketServidor();
    }
    
    public SocketServidor()
    {
         String cadena;
         int num;
         Scanner entrada=new Scanner(System.in);
       
        try
        {
            ServerSocket socket = new ServerSocket (40002);                               //Creacion del socket en el puerto 40002
            System.out.println ("Esperando cliente");
            Socket cliente = socket.accept();
            System.out.println ("Conectado con cliente de " + cliente.getInetAddress());
            cliente.setSoLinger (true, 10);
            
            DataInputStream bufferEntrada =new DataInputStream (cliente.getInputStream()); //Stream para leer
             
             DatoSocket dato=new DatoSocket(1," ");
             
             dato.readObject(bufferEntrada);         
             System.out.println ("Cliente dice " + dato.toString());                       //Se le envian al servidor los datos del cliente

             System.out.println ("Ingrese carctares: ");                                   //Se piden n+1 caracteres 
             cadena=entrada.nextLine();
            
            DatoSocket aux = new DatoSocket(dato.c,cadena);                               //Aux:objeto usado para el envio

            DataOutputStream bufferSalida =new DataOutputStream (cliente.getOutputStream());//Stream para la salida de datos 
            aux.writeObject (bufferSalida);                                                 //Envio de datos
            
            cliente.close();                                                                //cierre de ambos sockets
            socket.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}