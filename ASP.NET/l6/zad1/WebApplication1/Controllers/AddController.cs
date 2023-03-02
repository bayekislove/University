using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Controllers
{
    public class AddController : Controller
    {
        [HttpGet]
        public ActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Index(string q)
        {
            string title = Request.Form["Title"];
            string author = Request.Form["Author"];
            int pYear = int.Parse(Request.Form["PublicationYear"] != "" ? Request.Form["PublicationYear"] : "-1");

            if(title == "" || author == "" || pYear == -1)
            {
                return View();
            }
            using( var context = new KsiazkiDataContext())
            {
                var tab = context.Ksiazkis;
                if( tab.Where(x => x.Autor == author && x.Tytul == title && pYear == x.Rwydania ).Count() > 0)
                {
                    return View();
                }
                tab.InsertOnSubmit( new Ksiazki { Autor = author, Rwydania = pYear, Tytul = title } );
                context.SubmitChanges();
            }
            return Redirect("/");
        }
    }
}