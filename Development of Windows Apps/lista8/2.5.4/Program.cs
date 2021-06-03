using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2._5._4
{
    class Program
    {
        static void Main(string[] args)
        {
            using( var data = new StudenciDBContext())
            {
                Miejscowosc m1 = new Miejscowosc();
                m1.nazwa = "BER";
                data.Miejscowosc.Add(m1);

                Student nowy = new Student() { Imie = "K", Nazwisko = "B", DataUr = DateTime.Parse("01/01/1990") };
                nowy.Miejscowosc = m1;
                data.Student.Add(nowy);
                data.SaveChanges();

                data.Student.Where(x => x.Imie == "K").Take(1).Select(x => x).First().Nazwisko = "Ozeniony";
                data.SaveChanges();

                data.Miejscowosc.Remove(data.Miejscowosc.Where(x => x.nazwa == "BER").First());
                data.SaveChanges();
            }
            Console.ReadLine();
        }
    }

    public class StudenciDBContext : DbContext
    {
        public StudenciDBContext(string connString) : base(connString) { }

        public StudenciDBContext() : base("cs") { }

        public DbSet<Student> Student { get; set; }
        public DbSet<Miejscowosc> Miejscowosc { get; set; }

        /*protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            modelBuilder.Entity<Miejscowosc>().Property(Miejscowosc => Miejscowosc.nazwa).IsRequired().HasMaxLength(10);
            modelBuilder.Entity<Miejscowosc>()
                .HasMany(Miejscowosc => Miejscowosc.students)
                .WithRequired(x => x.Miejscowosc)
                .HasForeignKey(x => x.Miejscowosc);
            modelBuilder.Entity<Miejscowosc>().ToTable("Miejscowosc");
            modelBuilder.Entity<Student>().ToTable("Student");
        }*/
    }

    public class Student
    {
        [Key]
        public int ID { get; set; }
        public DateTime DataUr { get; set; }
        public string Imie { get; set; }
        public string Nazwisko { get; set; }
        public Miejscowosc Miejscowosc { get; set; }
    }

    public class Miejscowosc
    {
        [Key]
        public string nazwa { get; set; }
        public ICollection<Student> students { get; set; }
    }
}
