using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace class4
    {
        [TestClass]
        public class FactoryTests
        {
            [TestMethod]
            public void IfCreationOfSquareSuccessful()
            {
                ShapeFactory factory = new ShapeFactory();
                IShape square = factory.CreateShape("square", 3);

                Assert.IsNotNull(square);
            }

            [TestMethod]
            public void IfCreationOfRectangleSuccessful()
            {
                ShapeFactory factory = new ShapeFactory();
                IShape rectangle = factory.CreateShape("rectangle", 3, 4);

                Assert.IsNotNull(rectangle);
            }
        }   
    }
