public class HuffmanCodeTree
{
  private HuffmanNode node;
  public HuffmanCodeTree(HuffmanNode root)
  {
    node = root;
  }
//iterates over the charlst and calles the put method to add it to the tree
  public HuffmanCodeTree(HuffmanCodeBook book)
  {
    node= new HuffmanNode(null,null);
    char[] c = book.getCharlst();
    for(int i=0;i<c.length;i++)
    {
      this.put(book.getSequence(c[i]),c[i]);
      }
    }
   //for the length of the binary sequence it adds it to the tree once it is at the end it puts the char at the spot it arrives at
    public void put(BinarySequence sequence,char letter)
    {
      String x=sequence.toString();
      HuffmanNode nodecop = node;
      for(int i=0;i<x.length();i++)
      {
        if(x.charAt(i)=='1')
        {
          if(nodecop.getOne()==null)
          {
            nodecop.setOne(new HuffmanNode(null,null));
            nodecop=nodecop.getOne();
          }
          else
          {
            nodecop=nodecop.getOne();
          }
        }
          if(x.charAt(i)=='0')
        {
          if(nodecop.getZero()==null)
          {
            nodecop.setZero(new HuffmanNode(null,null));
            nodecop=nodecop.getZero();
          }
         else
          {
            nodecop=nodecop.getZero();
          }
        }
      }
      nodecop.setData(letter);
    }
    //goes down the tree untill it finds data then resets the getter and goes down the tree again untill it finds something
    public String decode(BinarySequence seq)
    {
      HuffmanNode nodecop=this.node;
      String str=seq.toString();
      StringBuilder sb = new StringBuilder();
        for(int i=0;i<str.length();i++)
      {
        if(str.charAt(i)=='1')
        {
            nodecop=nodecop.getOne();
        }
          if(str.charAt(i)=='0')
        {
            nodecop=nodecop.getZero();
        }
        if(nodecop.getData()!=null)
        {
          sb.append(nodecop.getData());
          nodecop=this.node;
        }
      }

      return sb.toString();
    }
    public boolean isValid()
    {
      return node.isValid();
    }
  }
