using System;
using System.Data;
using System.Data.OleDb;

namespace _2._5._1
{
    class Program
    {
        static void ReadDataOnOutput(string connectionString)
        {
            using(OleDbConnection conn = new OleDbConnection(connectionString))
            {
                conn.Open();
                OleDbDataAdapter objDA = new OleDbDataAdapter("select * from [Arkusz1$]", conn);

                DataSet excelDataSet = new DataSet();
                objDA.Fill(excelDataSet, "studenci");

                foreach (var m in excelDataSet.Tables[0].DefaultView)
                    Console.WriteLine(((DataRowView)m).Row.ItemArray[0] + 
                                        "\t" + ((DataRowView)m).Row.ItemArray[1] + 
                                        "\t" + ((DataRowView)m).Row.ItemArray[2] +
                                        "\t" + ((DataRowView)m).Row.ItemArray[3]);
            }
        }

        static void Main(string[] args)
        {
            //błąd z connection stringiem, nie mam excela na komputerze, więc nie mogę sprawdzić czy działa :( ale powinno
            ReadDataOnOutput("Provider=Microsoft.ACE.OLEDB.12.0; Data Source=zad.xlsx; Extended Properties='Excel 8.0;HDR=Yes'");
            Console.ReadLine();
        }
    }
}
