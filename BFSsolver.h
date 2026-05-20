












//t type and h hash function
template<typename T,typename H>
class BFSsolver
{
private:: 
    vector<RubiksCube::MOVE> moves; // list of moves to solve the cube
    unordered_map<T,bool,H> vis;
    unordered_map<T,RubiksCube::MOVE,H> prevmove; // move used to reach this state

    T bfs()
    {
        T node;
        queue<T> q;
        q.push(rcube);
        vis[rcube] = true;

        while(!q.empty())
        {
            node = q.front();
            q.pop();
            if(node.isSolved())
            {
                return node;
            }
            for(int i=0;i<18;i++)
            {
                auto cur_move =  RubiksCube::MOVE(i);
                node.move(cur_move);
                if(!vis[node])
                {
                    vis[node]=true;
                    prevmove[node]=cur_moove;
                    q.push(node);

                } 
                node.invert(cur_move);
            }
        }
        // compailar needs a return statement here but this line should never be reached
        return rcube;

    }


    public:

    T rcube; // current state of the cube

    BFSsolver(t cube)
    {
        rcube = cube;
    }

    vector<RubiksCube::MOVE> solve()
    {




    }