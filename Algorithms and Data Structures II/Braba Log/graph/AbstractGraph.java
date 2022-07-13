package graph;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public abstract class AbstractGraph implements GraphInterface, Cloneable
{
    protected static final int GRAPHVIZ_IMAGE_WIDTH = 2000;
    protected static final String GRAPHVIZ_FOLDER = "example/";
    protected static final String GRAPHVIZ_FILE_EXTENSION = ".png";
    private int numberOfVertices;
    private List<Vertex> vertices;

    protected AbstractGraph(List<Vertex> vertices)
    {
        numberOfVertices = vertices.size();
        setVertices(vertices);
    }

    protected AbstractGraph()
    {
        vertices = new ArrayList<>();
        numberOfVertices = 0;
    }

    @Override
    public void addVertex(Vertex vertex)
    {
        vertices.add(vertex);
        numberOfVertices = vertices.size();
    }

    public int getNumberOfVertices()
    {
        return numberOfVertices;
    }

    public void setNumberOfVertices(int numberOfVertices)
    {
        this.numberOfVertices = numberOfVertices;
    }

    public List<Vertex> getVertices()
    {
        return vertices;
    }

    public void setVertices(List<Vertex> vertices)
    {
        this.vertices = vertices;
    }

    public void addEdge(Vertex source, Vertex destination)
    {
        addEdge(source, destination, 1);
    }

    public Vertex getCentermostVertex(float[][] distanceMatrix)
    {
        float[] maxDistanceInCollumn = new float[distanceMatrix.length];
        Arrays.fill(maxDistanceInCollumn, Float.NEGATIVE_INFINITY);
        for (int i = 0; i < distanceMatrix.length; i++)
        {
            for (int j = 0; j < distanceMatrix[0].length; j++)
            {
                if (maxDistanceInCollumn[i] < distanceMatrix[i][j])
                {
                    maxDistanceInCollumn[i] = distanceMatrix[i][j];
                }
            }
        }
        int vertexIndex = getMinDistanceIndexInCollumn(maxDistanceInCollumn);
        return vertices.get(vertexIndex);
    }
    
    public Vertex getPerifericVertex(float[][] distanceMatrix)
    {
        float[] maxDistanceInCollumn = new float[distanceMatrix.length];
        Arrays.fill(maxDistanceInCollumn, Float.NEGATIVE_INFINITY);
        for (int i = 0; i < distanceMatrix.length; i++)
        {
            for (int j = 0; j < distanceMatrix[0].length; j++)
            {
                if (maxDistanceInCollumn[i] < distanceMatrix[i][j])
                {
                    maxDistanceInCollumn[i] = distanceMatrix[i][j];
                }
            }
        }
        int vertexIndex = getMaxDistanceIndexInCollumn(maxDistanceInCollumn);
        return vertices.get(vertexIndex);
    }
    
    // O vertice mais periferico é aquele com maior distancia
    // no vetor de distancias maximas, em oposicao ao vertice
    // mais central, que é aquele com menor distancia no vetor
    // de distancias maximas
    private int getMaxDistanceIndexInCollumn(float[] distanceArray)
    {
        int maxIndex = 0;
        float maxDistance = distanceArray[0];
        for (int i = 1; i < distanceArray.length; i++)
        {
            if (maxDistance < distanceArray[i])
            {
                maxDistance = distanceArray[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    private int getMinDistanceIndexInCollumn(float[] distanceArray)
    {
        int minIndex = 0;
        float minDistance = distanceArray[0];
        for (int i = 1; i < distanceArray.length; i++)
        {
            if (minDistance > distanceArray[i])
            {
                minDistance = distanceArray[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
    
    // Para achar o vertice mais distance do vertice mais periferico,
    // basta verificar na matriz de distancias, qual o vertice com maior
    // distancia daquele que é o mais periférico, ou seja, que está
    // no indice com maior valor no vetor distanceMatrix[perifericIndex].
    public Vertex getMostDistanceOfPeriferic(float[][] distanceMatrix)
    {
        Vertex periferic = getPerifericVertex(distanceMatrix);
        
        float[] maxDistanceInCollumn = new float[distanceMatrix.length];
        Arrays.fill(maxDistanceInCollumn, Float.NEGATIVE_INFINITY);
        
        System.arraycopy(distanceMatrix[getIndexOfVertex(periferic)], 0, maxDistanceInCollumn, 0, distanceMatrix.length);
        int indexOfTheFarest = 0;
        
        for (int i = 0; i < distanceMatrix.length; i++)
        {
            if (maxDistanceInCollumn[i] > maxDistanceInCollumn[indexOfTheFarest])
            {
                indexOfTheFarest = i;
            }
        }
        
        return vertices.get(indexOfTheFarest);
    }

    public int getIndexOfVertex(Vertex vertex)
    {
        return getVertices().indexOf(vertex);
    }

    @Override
    protected AbstractGraph clone() throws CloneNotSupportedException
    {
        AbstractGraph graphClone = (AbstractGraph)super.clone();
        graphClone.setNumberOfVertices(this.getNumberOfVertices());
        graphClone.setVertices(new ArrayList<>(this.getVertices()));
        return graphClone;
    }
}
