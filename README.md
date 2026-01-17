# Predictive-Text-Engine (C)

This project implements a Trie-based predictive text engine that suggests the most likely next letter
based on a given prefix and historical word usage frequencies.

### Key Features
- Efficient Trie data structure supporting dynamic word insertion
- Prefix-based prediction using cumulative frequency analysis
- Handles large input sizes with strict memory and performance constraints
- Alphabetically ordered tie-breaking for equally probable predictions
- No file I/O — processes all data via standard input/output for portability

### How It Works
- Words are inserted into a Trie along with their usage frequencies
- Each node tracks:
  - Word frequency
  - Prefix frequency sum
  - Maximum child frequency
- For a given prefix, the system analyzes child nodes to determine the most likely next character(s)

### Technologies & Concepts
- C programming
- Tries (Prefix Trees)
- Pointer-based data structures
- Memory management (malloc/free)
- Algorithmic optimization
