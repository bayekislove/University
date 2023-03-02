using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class5
{
    public class Person { }

    namespace NotifyInjection
    {
        public interface PersonNotifier
        {
            public void notifyPersons(IEnumerable<Person> persons);
        }

        public abstract class PersonMailNotifier : PersonNotifier
        {
            public void notifyPersons(IEnumerable<Person> persons) { }
        }

        public abstract class PersonRegistry
        {
            PersonNotifier notifier;
            IEnumerable<Person> persons;

            public PersonRegistry(PersonNotifier notifier)
            {
                this.notifier = notifier;
            }
            public abstract void getPersons();
            public void notifyPersons()
            {
                notifier.notifyPersons(persons);
            }
        }

        public class JSONPersonRegistry : PersonRegistry
        {
            public JSONPersonRegistry(PersonNotifier notifier) : base(notifier) { }

            public override void getPersons() { }
        }
    }

    namespace RegistryInjection
    {
        public interface PersonRegistry
        {
            public IEnumerable<Person> getPersons();
        }

        public class JSONPersonRegistry : PersonRegistry
        {
            public IEnumerable<Person> getPersons()
            {
                throw new NotImplementedException();
            }
        }
        
        public abstract class PersonNotifier
        {
            PersonRegistry registry;
            IEnumerable<Person> persons;

            public PersonNotifier(PersonRegistry registry)
            {
                this.registry = registry;
            }
            public abstract void notifyPersons();
        }

        public class MailPersonNotifier : PersonNotifier
        {
            public MailPersonNotifier(PersonRegistry registry) : base(registry) { }
            public override void notifyPersons() { }
        }
    }
}
