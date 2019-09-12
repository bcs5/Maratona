/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
		SimpleDateFormat f = new SimpleDateFormat("dd/MM/yyyy");
		Timestamp timestamp1 = new Timestamp(f.parse("14/11/2008").getTime());
		Timestamp timestamp2 = new Timestamp(f.parse("15/11/2008").getTime());
		System.out.println(timestamp1.before(timestamp2));
	}
}
