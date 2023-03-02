using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public interface Strategy
    {
        public void Connect();
        public void Download();
        public void Process();
        public void Disconnect();
    }

    public class DataAccess
    {
        public Strategy strategy;

        public DataAccess(Strategy strategy)
        {
            this.strategy = strategy; 
        }

        public void Execute()
        {
            strategy.Connect();
            strategy.Download();
            strategy.Process();
            strategy.Disconnect();
        }
    }

    public class DbDataAccess : Strategy
    {
        private SQLiteConnection conn;
        private List<int> idlist;
        private int idsum;

        public void Connect()
        {
            conn = new SQLiteConnection("Data Source=database.db; Version = 3; New = True; Compress = True;");
            try
            {
                conn.Open();
            }
            catch (Exception)
            {

            }
        }

        public void Disconnect()
        {
            try
            {
                conn.Close();
            }
            catch (Exception)
            {

            }
        }

        public void Download()
        {
            SQLiteDataReader sqlite_datareader;
            SQLiteCommand sqlite_cmd;
            sqlite_cmd = conn.CreateCommand();
            sqlite_cmd.CommandText = "SELECT id FROM Customers";

            sqlite_datareader = sqlite_cmd.ExecuteReader();
            while (sqlite_datareader.Read())
            {
                string myreader = sqlite_datareader.GetString(0);
                idlist.Add(int.Parse(myreader));
            }
            conn.Close();
        }

        public void Process()
        {
            idsum = idlist.Sum();
        }
    }

    //z XML robimy analogicznie
    public class XMLDataAccess
    {

    }
}
