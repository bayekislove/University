using Markdig;
using MVCCMSRouting.Models.Page;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MVCCMSRouting.Controllers
{
    public class PageController : Controller
    {
        [HttpGet]
        public ActionResult Render()
        {
            var routeData = this.Request.RequestContext.RouteData.Values;

            string site = routeData[CMSCustomRoute.SITENAME] as string;
            string page;
            if (routeData[CMSCustomRoute.PAGENAME] as string == "index.html")
            {
                page = "index.html";
            }
            else
            {
                page = routeData[CMSCustomRoute.PAGENAME] as string + ".html";
            }
            string content;

            using (var context = new StronyDataContext())
            {
                var matches = context.Stronies.Where(x => x.Name.Replace("\\", "/") == (site + "/" + page));
                if (matches.Count() == 0)
                {
                    return Content("Strona nieodnaleziona!");
                }
                else
                {
                    content = Markdown.ToHtml(matches.First().Page);
                }
            }

            // renderowanie
            var model = new PageRenderModel()
            {
                Site = site,
                Page = page,
                Content = content
            };

            return View(model);
        }

        [HttpPost]
        public ActionResult Render(string q)
        {
            if (Request.Form["route"] == "")
            {
                return View();
            }
            using (var context = new StronyDataContext())
            {
                var matches = context.Stronies.Where(x => x.Name == Request.Form["route"]);
                var routeData = this.Request.RequestContext.RouteData.Values;
                string site = routeData[CMSCustomRoute.SITENAME] as string;
                if (matches.Count() == 0)
                {
                    string name = site + "/" + Request.Form["route"];
                    Strony help = new Strony(){ Name = name, Page = "Auto generated" };
                    context.Stronies.InsertOnSubmit(help);
                    context.SubmitChanges();
                }
            }

            return Redirect("/CMS/a/b/c");
        }

        public ActionResult SavePage(string content)
        {
            var routeData = this.Request.RequestContext.RouteData.Values;
            string site = routeData[CMSCustomRoute.SITENAME] as string;
            string page = routeData[CMSCustomRoute.PAGENAME] as string;

            using ( var context = new StronyDataContext())
            {
                var matches = context.Stronies.Where(x => x.Name.Replace("\\", "/") == (site + "/" + page));
                if (matches.Count() == 0)
                {
                    return Content("Najpierw dodaj stronę, której zawartość chcesz zmienić!");
                }

                matches.First().Page = content;
                context.SubmitChanges();

                var model = new PageRenderModel()
                {
                    Site = site,
                    Page = page,
                    Content = content
                };

                return View(model);
            }
        }
    }
}