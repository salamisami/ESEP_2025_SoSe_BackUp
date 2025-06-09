#ifndef PIECE_QUEUE_H
#define PIECE_QUEUE_H

#include <string>

// Enum for the state of the piece (Zustand)
enum class PieceState {
    NEW_PIECE,
    HEIGHT_MEASURED,
    METAL_DETECTION,
    TO_SORT_1,
    TO_SORT_2,
    SORTED_OUT_1,
    SORTED_OUT_2,
    OK,
    FEHLER,
    READY_4_PICKUP
};

// Struct representing a piece (Werkstück)
struct Piece {
    std::string typ;          // String type
    int id;                   // Unique identifier
    PieceState zustand;       // Current state of the piece
    bool wurdeGeprueft;       // Whether the piece has been checked
    bool korrektSortiert;     // Whether the piece is correctly sorted
    bool hoch;                // Whether the piece is high (height-related)
    bool metall;              // Whether the piece is metal
    bool bohrung;             // Whether the piece has a bore (drill hole)
};

#endif // PIECE_QUEUE_H