using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public enum CoffeeType
    {
        None,
        Espresso,
        Doppio,
        Ristretto
    }

    public interface State
    {
        public void Wait();
        public void ChooseCoffee(CoffeeType coffee);
        public void MakeCoffee();
    }

    public class ChooseCoffeState : State
    {
        public StateMachine machine;
        public CoffeeType type { get; set; }

        public ChooseCoffeState(StateMachine machine)
        {
            this.type = CoffeeType.None;
            this.machine = machine;
        }

        public void ChooseCoffee(CoffeeType coffee)
        {
            type = coffee;
        }

        public void MakeCoffee()
        {
            machine.selected = type;
            this.type = CoffeeType.None;
            machine.SetState(new MakeState(machine));
        }

        public void Wait()
        {
        }
    }

    public class WaitState : State
    {
        public StateMachine machine;

        public WaitState(StateMachine machine)
        {
            this.machine = machine;
        }

        public void ChooseCoffee(CoffeeType coffee)
        {
            this.machine.SetState(new ChooseCoffeState(machine));
        }

        public void MakeCoffee()
        {
            throw new Exception("select coffee first!");
        }

        public void Wait()
        {
        }
    }

    public class MakeState : State
    {
        public StateMachine machine;

        public MakeState(StateMachine machine)
        {
            this.machine = machine;
        }

        public void ChooseCoffee(CoffeeType coffee)
        {
            throw new Exception("Coffe cant be changed");
        }

        public void MakeCoffee()
        {
            throw new NotImplementedException();
        }

        public void Wait()
        {
            this.machine.SetState(new WaitState(machine));
        }
    }

    public class StateMachine
    {
        private State current;
        public CoffeeType selected { get; set; }

        public StateMachine()
        {
            current = new WaitState(this);
        }

        public void SetState(State state)
        {
            this.current = state;
        }
    }
}
