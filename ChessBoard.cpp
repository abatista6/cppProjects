class Board
    {
        public enum PieceColor { None, White, Black};
        public enum PieceType { Empty, Pawn, Rook, Knight, Bishop, Queen, King};
        public enum Col {a, b, c, d, e, f, g, h};
        public enum Row { eight, seven, six, five, four, three, two, one }

        public struct BoardLocation
        {
            public Row row;
            public Col col;
        }

        public struct piece
        {
            public PieceColor color;
            public PieceType type;
            public Button graphic;

            public piece(PieceColor c, PieceType t, Button g)
            {
                color = c;
                type = t;
                graphic = g;
            }

        }

        private piece[,] BoardState = new piece[8, 8];

        public bool SquareOccupied(Point p)
        {
            piece piece = BoardState[p.X, p.Y];
            if (piece.type != PieceType.Empty) return true;
            else return false;
        }

        public Button GetButton(Point p)
        {
            piece piece = BoardState[p.X, p.Y];
            return piece.graphic;
        }

        public Board()
        {
        }

        public void MakeMove(Point from, Point to, Button graphic)  
        {
            BoardLocation bFrom = new BoardLocation();
            BoardLocation bTo = new BoardLocation();

            bFrom.col = (Col)from.X;
            bFrom.row = (Row)from.Y;
            bTo.col = (Col)to.X;
            bTo.row = (Row)to.Y;
            MakeMove(bFrom, bTo, graphic);
        }

        public void MakeMove(BoardLocation from, BoardLocation to, Button graphic)
        {
            BoardState[(int)to.col, (int)to.row] = BoardState[(int)from.col, (int)from.row];
            BoardState[(int)from.col, (int)from.row] = new piece(PieceColor.None, PieceType.Empty, null);
        }

        public void SetBoardPiece(Point pointLoc, PieceColor color, PieceType type, Button b)
        {
            BoardLocation bLoc = new BoardLocation();

            bLoc.col = (Col)pointLoc.X;
            bLoc.row = (Row)pointLoc.Y;
            SetBoardPiece(bLoc.col,bLoc.row, color, type, b);
        }

        public void SetBoardPiece(Col col, Row row, PieceColor color, PieceType type, Button b)
        {
            BoardState[(int)col, (int)row] = new piece(color, type, b);
        }
    }