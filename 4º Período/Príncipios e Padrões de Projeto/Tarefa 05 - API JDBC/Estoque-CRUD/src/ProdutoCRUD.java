import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

 class ProdutoCRUD {

     //Metodo create
     public void criarProduto(String nome, String descricao, double preco, int estoque) {
         String sql = "INSERT INTO produtos (nome, descricao, preco, estoque) VALUES (?, ?, ?, ?)";

         try (Connection conn = DatabaseConnection.getConnection();
              PreparedStatement stmt = conn.prepareStatement(sql)) {

             stmt.setString(1, nome);
             stmt.setString(2, descricao);
             stmt.setDouble(3, preco);
             stmt.setInt(4, estoque);
             stmt.executeUpdate();

             System.out.println("Produto adicionado com sucesso!");
         }
         catch (SQLException e) {
             e.printStackTrace();
         }
     }

     //Metodo read
     public List<String> lerProdutos() {
         List<String> listaProdutos = new ArrayList<>();
         String sql = "SELECT * FROM produtos";

         try (Connection conn = DatabaseConnection.getConnection();
              PreparedStatement stmt = conn.prepareStatement(sql);
              ResultSet rs = stmt.executeQuery()) {

             while (rs.next()) {
                 String produtoFormatado = String.format(
                         "ID: %-4d Nome: %-30s\n" +
                                 "Descrição: %-50s\n" +
                                 "Preço: R$ %-10.2f Estoque: %-4d\n" +
                                 "-----------------------------------------------------------------------------------",
                         rs.getInt("id"),
                         rs.getString("nome"),
                         rs.getString("descricao"),
                         rs.getDouble("preco"),
                         rs.getInt("estoque")
                 );

                 listaProdutos.add(produtoFormatado);
             }
         } catch (SQLException e) {
             e.printStackTrace();
         }

         return listaProdutos;
     }

     //Metodo atualizar
     public void atualizarProduto(int id, int quantidade){
         String sql = "UPDATE produtos SET estoque = estoque + ? WHERE id = ?";

         try(Connection conn = DatabaseConnection.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)){

             stmt.setInt(1, quantidade);
             stmt.setInt(2, id);
             int linhasAfetadas = stmt.executeUpdate();

             if(linhasAfetadas > 0){
                 System.out.println("Estoque atualizado com sucesso!");
             }else{
                 System.out.println("Produto não encontrado!");
             }
         }
         catch (SQLException e) {
             e.printStackTrace();
         }
     }

     //Metodo remover
     public void excluirProduto(int id){
         String sql = "DELETE FROM produtos WHERE id = ?";

         try(Connection conn = DatabaseConnection.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)){

             stmt.setInt(1, id);
             int linhasAfetadas = stmt.executeUpdate();

             if(linhasAfetadas > 0){
                 System.out.println("Produto removido com sucesso!");
             }else{
                 System.out.println("Produto não encontrado.");
             }
         }
         catch (SQLException e) {
             e.printStackTrace();
         }
     }

     public int obterQuantidadeProduto(int id) {
         String sql = "SELECT estoque FROM produtos WHERE id = ?";
         try (Connection conn = DatabaseConnection.getConnection();
              PreparedStatement stmt = conn.prepareStatement(sql)) {
             stmt.setInt(1, id);
             ResultSet rs = stmt.executeQuery();

             if (rs.next()) {
                 return rs.getInt("estoque");
             } else {
                 return -1;
             }
         } catch (SQLException e) {
             e.printStackTrace();
             return -1;
         }
     }

 }
