using System.Collections.Generic;
using System.Linq;

namespace WebApplication1.Models
{
    public class WebGridDemoIndexModel
    {
        public PagedEnumerable<User> Users { get; set; }
    }

    public class PagedEnumerable<T>
    {
        public int CurrentPage { get; set; }
        public int PageSize { get; set; }
        public int TotalCount { get; set; }

        public IEnumerable<T> Items { get; set; }
    }

    public class DataLayer
    {
        public IEnumerable<User> GetUsers(string OrderBy, int StartRow, int RowCount)
        {
            IEnumerable<User> model = StaticModel.Users;

            using (var context = new KsiazkiDataContext())
            {
                model = context.Ksiazkis.Select(x => new User
                {
                    ID = x.id,
                    Title = x.Tytul,
                    Author = x.Autor,
                    PYear = x.Rwydania
                }).ToList();
            }

            return model.Skip(StartRow).Take(RowCount);
        }

        public int TotalUsers()
        {
            return StaticModel.Users.Count;
        }
    }

    public class StaticModel
    {
        static StaticModel()
        {
            Users = new List<User>();
            using (var context = new KsiazkiDataContext())
            {
                Users = context.Ksiazkis.Select(x => new User
                {
                    ID = x.id,
                    Title = x.Tytul,
                    Author = x.Autor,
                    PYear = x.Rwydania
                }).ToList();
            }
        }

        public static List<User> Users { get; private set; }
    }

    public class User
    {
        public int ID { get; set; }
        public string Title { get; set; }
        public string Author { get; set; }
        public int PYear { get; set; }
    }
}