package graph;

import java.util.logging.Logger;

public class FloydWarshallTraversal extends TraversalStrategyInterface
{
    private static final Logger LOGGER = Logger.getLogger("FloydWarshallTraversal.class");

    private float [][]distanceMatrix;

    public float[][] getDistanceMatrix()
    {
        return distanceMatrix;
    }

    public void setDistanceMatrix(float[][] distanceMatrix)
    {
        this.distanceMatrix = distanceMatrix;
    }

    public FloydWarshallTraversal(AbstractGraph graph)
    {
        super(graph);
        distanceMatrix = new float[graph.getNumberOfVertices()][graph.getNumberOfVertices()];
    }

    @Override
    void traverseGraph(Vertex source)
    {
        for (int i = 0; i < getGraph().getNumberOfVertices(); i++)
        {
            for (int j = 0; j < getGraph().getNumberOfVertices(); j++)
            {
                Vertex origin = getGraph().getVertices().get(i);
                Vertex destination = getGraph().getVertices().get(j);
                if(getGraph().edgeExists(origin, destination))
                {
                    distanceMatrix[i][j] = getGraph().getDistance(origin, destination);
                    distanceMatrix[j][i] = getGraph().getDistance(destination, origin);
                }
                else
                {
                    distanceMatrix[i][j] = Float.POSITIVE_INFINITY;
                    distanceMatrix[j][i] = Float.POSITIVE_INFINITY;
                }
            }
        }

        for (int k = 0; k < getGraph().getNumberOfVertices(); k++)
        {
            for (int i = 0; i < getGraph().getNumberOfVertices(); i++)
            {
                for (int j = 0; j < getGraph().getNumberOfVertices(); j++)
                {
                    if ((distanceMatrix[i][k] + distanceMatrix[k][j]) < distanceMatrix[i][j])
                    {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    }
                }
            }
        }
        
        for (int i = 0; i < getGraph().getNumberOfVertices(); i++)
        {
            distanceMatrix[i][i] = 0;
        }
    }
}
