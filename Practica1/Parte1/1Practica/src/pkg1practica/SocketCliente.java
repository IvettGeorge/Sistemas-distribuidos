package pkg1practica;

import java.net.*;
import java.io.*;
import java.util.Scanner;

public class SocketCliente
 {
     public static void main (String [] args)
     {
         new SocketCliente();
     }
    
     public SocketCliente()
     {
         String cadena;
         int num;
         Scanner entrada=new Scanner(System.in);
         try
         {
             Socket socket = new Socket ("localhost", 40002);                                    /* Se crea el socket cliente 10.0.2.15 */
             System.out.println ("conectado");
             
             socket.setSoLinger (true, 10);
             DataOutputStream bufferSalida =new DataOutputStream (socket.getOutputStream());      //Stream para el encio de datos
              
             System.out.println ("Ingrese numero: ");                                             //Primero se da el numero de caracteres
             cadena=entrada.nextLine();
             num=Integer.valueOf(cadena)+1;
             
             System.out.println ("Ingrese carctares: ");                                          //Se ingresan los caracteres
             cadena=entrada.nextLine();
        
             DatoSocket aux = new DatoSocket (num,cadena);                                        //Envio de datos, primero se envian a la
             aux.writeObject (bufferSalida);                                                      //clase, para tener las adaptaciones al 
                                                                                                  //formato red estándar.
     
             DataInputStream bufferEntrada =new DataInputStream (socket.getInputStream());        /* Se obtiene un stream de lectura */
       
             DatoSocket dato=new DatoSocket(1," ");
             dato.readObject(bufferEntrada);
             System.out.println ("Servidor dice " + dato.toString());                              //Se muestran los datos recibidos
             
             socket.close();                                                                       //Cierre del socket
         }
         catch (Exception e)
         {
             e.printStackTrace();
         }
     }
}