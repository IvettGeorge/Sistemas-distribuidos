package pkg1practica;

import java.io.*;

/** Formato red estándar */
public class DatoSocket implements Serializable
 {
   public DatoSocket (int num,String cadena)
   {
      if (cadena != null)
      {
         c = num;
         d = cadena;
      }
   }

   public int c = 0;
   public String d = "";
     
   public String toString ()
   {
       String resultado;
       resultado = Integer.toString(c) + " -- " + d;
       return resultado;
   }
   
   //Traduccion de java a C
   public void writeObject(java.io.DataOutputStream out)
         throws IOException
     {
         out.writeInt (c+1);
         out.writeBytes (d);
         out.writeByte ('\0');
     }
    
     //Traduccion de C a java
     public void readObject(java.io.DataInputStream in)
     throws IOException
     {
         c = in.readInt() - 1;                                                   // Se lee la longitud de la cadena y se le resta 1 para eliminar el caracter especial
         byte [] aux = null;
         
         aux = new byte[c];                                                      // Se le da el tamaño 
         in.read(aux, 0, c);                                                     // Se leen los bytes
         d = new String (aux);                                                   // Se convierten a String
         in.read(aux,0,1);                                                       // Se lee el \0
     }
}
