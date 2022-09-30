 class Main {
 public static void main(String[] args) {
        HuffmanCodeBook book = ProvidedHuffmanCodeBook.getEbookHuffmanCodebook();
        HuffmanCodeTree tree = new HuffmanCodeTree(book);

        /////////////////////////////////////////////////
        // TEST 1: Simple DecodeEncode (2 points)
        /////////////////////////////////////////////////
        String original = "Once upon a midnight dreary, while I pondered, weak and weary,\n" +
                "Over many a quaint and curious volume of forgotten lore—\n" +
                "    While I nodded, nearly napping, suddenly there came a tapping,\n" +
                "As of some one gently rapping, rapping at my chamber door.\n" +
                "\"'Tis some visitor,\" I muttered, \"tapping at my chamber door—\n" +
                "            Only this and nothing more.\"";
        BinarySequence encoded = book.encode(original);
        System.out.println(encoded);
        String decoded = tree.decode(encoded);
        System.out.println(original.equals(decoded));
        System.out.println(decoded);

        /////////////////////////////////////////////////
        // Test 2: DecodeEncode real file (2 points)
        // this will assume that you've got the right test files in the right folder.
        // see the FileIOAssistance to get that setup. If you can't get it setup don't sweat it too much
        // the autograder will be setup right, and if you past test 1 you probably pass test 2.
        /////////////////////////////////////////////////
        String bookFileID = "16-0";
        String bookFile = bookFileID + ".txt";
        // read the book
        String bookText = FileIOAssistance.readFile(bookFile);
        // encode it
        BinarySequence studentEncode = book.encode(bookText);

        // check that it's good.
        BinarySequence expectedEncode = BinarySequence.readFromFile(bookFile + ".enc");
        System.out.println(expectedEncode.equals(studentEncode));

        // store it to a file.
        studentEncode.writeToFile(bookFile + ".student.enc");

        // read it back and decode it!
        studentEncode = BinarySequence.readFromFile(bookFile + ".student.enc");
        System.out.println(expectedEncode.equals(studentEncode));
        decoded = tree.decode(studentEncode);
        FileIOAssistance.writeFile(bookFileID + ".student.txt", decoded);
        System.out.println("Go check " + bookFileID + ".student.txt it should be peter pan.");

        /////////////////////////////////////////////////
        // Test 3 (not in autograder -- this one's just for you)
        // This should run pretty quickly -- a second or two depending on computer.
        // decode the other test files.
        /////////////////////////////////////////////////
        String[] files = {
                "23-0.txt",
                "36-0.txt",
                "43-0.txt",
                "84-0.txt",
                "345-0.txt",
                "829-0.txt",
                "1661-0.txt",
                "4300-0.txt",
                "6130-0.txt",
                "pg46.txt",
                "pg996.txt",
                "pg64317.txt"};
        for(String file : files) {
            BinarySequence code = BinarySequence.readFromFile(file+".enc");
            String text = tree.decode(code);
            FileIOAssistance.writeFile(file, text);
        }
        // for extra fun -- go check out the file size of the encoded and not encoded files!








    }
}