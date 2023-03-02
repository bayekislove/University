using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class6
{
    public abstract class Tree
    {
    }

    public class TreeNode : Tree
    {
        public Tree Left { get; set; }
        public Tree Right { get; set; }
    }

    public class TreeLeaf : Tree
    {
        public int Value { get; set; }
    }

    public abstract class TreeVisitor
    {
        // ta metoda nie jest potrzebna ale ułatwia korzystanie z Visitora
        public int? Visit(Tree tree)
        {
            if (tree is TreeNode)
                return VisitNode((TreeNode)tree);
            if (tree is TreeLeaf)
                return VisitLeaf((TreeLeaf)tree);
            return null;
        }
        public abstract int? VisitNode(TreeNode node);

        public abstract int? VisitLeaf(TreeLeaf leaf);

    }

    public class TreeHeightVisitor : TreeVisitor
    {
        public override int? VisitLeaf(TreeLeaf leaf)
        {
            return 0;
        }

        public override int? VisitNode(TreeNode node)
        {
            return Math.Max((int)Visit(node.Left), (int)Visit(node.Right)) + 1;
        }
    }
}
