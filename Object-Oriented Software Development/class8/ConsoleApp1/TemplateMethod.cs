using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace ConsoleApp1
{
    public abstract class DataAccessHandler 
    {
        protected abstract void Connect();
        protected abstract void Download();
        protected abstract void Process();
        protected abstract void Disconnect();

        public void Execute()
        {
            this.Connect();
            this.Download();
            this.Process();
            this.Disconnect();
        }
    }

    public class DbDataAccessHandler : DataAccessHandler
    {
        private SQLiteConnection conn;
        private List<int> idlist;
        private int idsum;

        protected override void Connect()
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

        protected override void Disconnect()
        {
            try
            {
                conn.Close();
            }
            catch (Exception)
            {

            }
        }

        protected override void Download()
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

        protected override void Process()
        {
            idsum = idlist.Sum();
        }
    }

    public class XMLDataAccessHandler : DataAccessHandler
    {
        private XmlDocument document;
        private string path;
        public XmlNode result;

        public XMLDataAccessHandler(string path)
        {
            this.path = path;
            document = new XmlDocument();
        }

        protected override void Connect()
        {
            
        }

        protected override void Disconnect()
        {

        }

        protected override void Download()
        {
            this.document.Load(this.path);
        }

        protected override void Process()
        {
            result = document.ParentNode;
            foreach(XmlNode node in document)
            {
                result = (node.Name.Length > result.Name.Length) ? node : result;
            }    
        }
    }
}
