using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;

namespace zad7
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnUploadClick(object sender, EventArgs e)
        {
            HttpPostedFile file = Request.Files["myFile"];
            if (file != null && file.ContentLength > 0)
            {
                XmlDocument doc = new XmlDocument();

                XmlNode declaration = doc.CreateNode(XmlNodeType.XmlDeclaration, null, null);
                doc.AppendChild(declaration);

                XmlElement root = doc.CreateElement("opis");
                doc.AppendChild(root);

                XmlElement nazwa = doc.CreateElement("nazwa");
                nazwa.InnerText = file.FileName;
                root.AppendChild(nazwa);

                XmlElement rozmiar = doc.CreateElement("rozmiar");
                rozmiar.InnerText = (file.ContentLength / 1024).ToString() + "KB";
                root.AppendChild(rozmiar);

                XmlElement sygnatura = doc.CreateElement("sygnatura");
                sygnatura.InnerText = (file.ContentLength % 0xFFFF).ToString();
                root.AppendChild(sygnatura);

                Response.Clear();
                Response.ClearHeaders();
                Response.ContentType = "file/xml";
                Response.Headers.Add("Content-Disposition", "attachment; filename=plik.xml");
                Response.ContentEncoding = System.Text.Encoding.UTF8;
                doc.Save(Response.Output);
                Response.End();
            }
        }
    }
}