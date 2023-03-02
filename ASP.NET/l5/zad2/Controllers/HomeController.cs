using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Mvc;
using System.Xml;

namespace zad2.Controllers
{
    public class HomeController : Controller
    {
        [HttpGet]
        public ActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Index(HttpPostedFileBase file)
        {

            if( file.ContentLength <= 0)
            {
                return Content("Wrzuć poprawny plik!");
            }
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
            return File(Encoding.Default.GetBytes(doc.OuterXml), "file/xml");
        }
    }
}