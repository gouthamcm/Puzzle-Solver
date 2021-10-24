#include <iostream>
#define MAX_SIZE 26
using namespace std;

class TrieData
{
private:
    TrieData *children_nodes[MAX_SIZE];
    bool end_of_word;

public:
    TrieData *root = NULL;
    TrieData *make_node()
    {
        TrieData *new_node = (TrieData *)malloc(sizeof(TrieData));

        for (int i = 0; i < MAX_SIZE; i++)
        {
            new_node->children_nodes[i] = NULL;
        }
        new_node->end_of_word = false;

        return new_node;
    }

    void insert_query(TrieData *root, string query)
    {
        TrieData *temp;
        //temporary variable to store the root node
        int index;

        if (query.length() == 0)
        {
            cout << "No string to be inserted";
            return;
        }
        temp = root;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                temp->children_nodes[index] = make_node();
            }
            temp = temp->children_nodes[index];
        }
        temp->end_of_word = true;
    }
    bool search_query(TrieData *root, string query)
    {
        if (query.length() == 0)
        {
            return false;
        }
        if (!root)
        {
            cout << "hi\n";
            return false;
        }
        TrieData *temp = root;
        int index;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                return false;
            }
            else
            {
                temp = temp->children_nodes[index];
            }
        }
        return temp->end_of_word;
    }
    void solver(char **board, int ROW_SIZE, int COL_SIZE, TrieData *root)
    {
        int visited[ROW_SIZE][COL_SIZE] = {0};
        for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int j = 0; j < COL_SIZE; j++)
            {
                string word = "";
                dfs(board, ROW_SIZE, COL_SIZE, i, j, root, word);
            }
        }
    }
    void dfs(char **board, int ROW_SIZE, int COL_SIZE, int x_pos, int y_pos, TrieData *node, string word)
    {
        if (x_pos < ROW_SIZE || y_pos < COL_SIZE)
            return;
        else if (x_pos == ROW_SIZE || y_pos == COL_SIZE)
            return;
        else if (board[x_pos][y_pos] == ' ')
            return;
        else
        {
            int index = board[x_pos][y_pos] - 'a';
            if (node->children_nodes[index])
            {

                word.push_back(board[x_pos][y_pos]);
                
                
                node = node->children_nodes[index];
                if (node->end_of_word)
                {
                    cout << word << endl;
                }
                char temp = board[x_pos][y_pos];
                board[x_pos][y_pos]=' ';
                dfs(board, ROW_SIZE, COL_SIZE, x_pos + 1, y_pos, node, word);
                dfs(board, ROW_SIZE, COL_SIZE, x_pos, y_pos + 1, node, word);
                dfs(board, ROW_SIZE, COL_SIZE, x_pos - 1, y_pos, node, word);
                dfs(board, ROW_SIZE, COL_SIZE, x_pos, y_pos - 1, node, word);
                board[x_pos][y_pos] = temp;
            }
        }
    }
    void insert(string query)
    {
        if (!root)
        {
            root = make_node();
        }
        insert_query(root, query);
    }
    bool search(string query)
    {
        return search_query(root, query);
    }
    void find_the_words(char **boards, int ROW_SIZE, int COL_SIZE)
    {
        solver(boards, ROW_SIZE, COL_SIZE, root);
    }
};

int main()
{
    int row, col, X;
    TrieData ob;
    cin >> row >> col;
    char **boards;
    boards = new char *[row];
    for (int i = 0; i < row; i++)
    {
        boards[i] = new char[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> boards[i][j];
        }
    }
    cin >> X;
    for (int i = 0; i < X; i++)
    {
        string inp;
        cin >> inp;
        ob.insert(inp);
    }
    ob.find_the_words(boards, row, col);
    return 0;
}