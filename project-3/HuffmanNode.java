public class HuffmanNode
{
  private HuffmanNode left;
  private HuffmanNode right;
  private Character data;
  //constructer for a branch
  public HuffmanNode(HuffmanNode right,HuffmanNode left)
  {
    this.data=null;
    this.left=left;
    this.right=right;
  }
  //construicter for a node with data
  public HuffmanNode(char data)
  {
    this.left=null;
    this.right=null;
    this.data=data;
  }

  public HuffmanNode getOne()
  {
    return this.left;
  }
  public void setOne(HuffmanNode left)
  {
    this.left=left;
  }
  public HuffmanNode getZero()
  {
    return this.right;
  }
  public void setZero(HuffmanNode right)
  {
    this.right = right;
  }
  public Character getData()
  {
    return data;
  }
  public void setData(char x)
  {
    this.data=x;
  }
  public boolean isLeaf()
  {
    if(this.left==null&this.right==null)
    {
      return true;
    }
    return false;
  }
  //uses recursion to check if the tree is valid the big logical equation basically says if not (valid) and not (other valid ) then it is not valid the other if statement is if this is a leaf/at the end of the tree return true it recursivly gets every item in the tree
  public boolean isValid()
  {
    if(!(this.data!=null&&(this.left==null&&this.right==null))&&!(this.data==null&&(this.left!=null&&this.right!=null)))
    {
      return false;
    }
    if(this.data!=null&&(this.left==null&&this.right==null))
    {
      return true;
    }
    return(this.left.isValid()&&this.right.isValid());

  }
}
