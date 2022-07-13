package graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.logging.Logger;


public final class GraphController
{
    private static final Logger LOGGER = Logger.getLogger("GraphController.class");

    private static AbstractGraph g;

    private static float calculeDistance(Vertex cidade1, Vertex cidade2) 
    {
        // d = raiz ( (Xa-Xb)² + (Ya-Yb)² )
        float distance = (float) Math.sqrt( Math.pow((cidade1.getX() - cidade2.getX()),2) + 
                                            Math.pow((cidade1.getY() - cidade2.getY()),2) );
        return distance;
    }
    
    private TraversalStrategyInterface traversalStrategy;
    private final List<Vertex> vertices;
    public static Map<String, Vertex> map;

    private GraphController()
    {
        vertices = createVertexAndEdgesList();
    }

    public static void main(String[] args)
    {
        GraphController graphController = new GraphController();
        graphController.test("MatrixGraph");
    }

    private static List<Vertex> createVertexAndEdgesList()
    {
        List<Vertex> vertices = new ArrayList<>();
        GraphController.map = new HashMap<>();
        
        Scanner input = new Scanner(System.in);
        
        int numberOfVertices;
        numberOfVertices = input.nextInt();
        
        for (int i = 0; i < numberOfVertices; i++)
        {
            // Outra funcao que deveria fazer esse servico de ajustar a leitura
            // é a useDelimiter() da classe Scanner, porém, ela só funcionou com
            // o netbeans e com o make em sistemas Unix. Por algum motivo, o makefile
            // rodando no windows não funciona com ela. 
            String string = input.next();
            String[] split = string.split(","); 

            int x = Integer.valueOf(split[0].trim());
            int y = Integer.valueOf(split[1].trim());
            
            Vertex umVertex = new Vertex(x,y);
            vertices.add(umVertex);
            GraphController.map.put(x + "," + y, umVertex);
        }
        
        g = new GraphMatrix(vertices);
        
        int numberOfEdges = input.nextInt();
        
        for (int i = 0; i < numberOfEdges; i++)
        {         
            String string = input.next();
            String[] split = string.split(":"); 
            String[] splitCity1 = split[0].split(",");
            String[] splitCity2 = split[1].split(",");
            
            int x1 = Integer.valueOf(splitCity1[0].trim());
            int y1 = Integer.valueOf(splitCity1[1].trim());     
            
            int x2 = Integer.valueOf(splitCity2[0].trim());
            int y2 = Integer.valueOf(splitCity2[1].trim()); 
            
            Vertex cidade1 = GraphController.map.get(x1 + "," + y1);
            Vertex cidade2 = GraphController.map.get(x2 + "," + y2);
            
            float distance = calculeDistance(cidade1, cidade2);
            g.addEdge(cidade1, cidade2, distance);
        }
        
        return vertices;
    }

    private void test(String fileName)
    {
        createTest();
        printTest(fileName);
    }

    private void printTest(String fileName)
    {
        traversalStrategy.traverseGraph(g.getVertices().get(0));
        if (traversalStrategy instanceof FloydWarshallTraversal)
        {
            Vertex center = g.getCentermostVertex(((FloydWarshallTraversal)traversalStrategy).getDistanceMatrix());
            System.out.println(center);
            
            Vertex periferic = g.getPerifericVertex(((FloydWarshallTraversal)traversalStrategy).getDistanceMatrix());
            System.out.println(periferic);
            
            Vertex farest = g.getMostDistanceOfPeriferic(((FloydWarshallTraversal)traversalStrategy).getDistanceMatrix());
            System.out.println(farest);
        }
    }

    private void createTest()
    {
        traversalStrategy = new FloydWarshallTraversal(g);
    }
}