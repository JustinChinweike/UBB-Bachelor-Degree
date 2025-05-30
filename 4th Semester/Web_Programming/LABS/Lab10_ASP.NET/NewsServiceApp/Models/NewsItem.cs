using System.ComponentModel.DataAnnotations;

namespace NewsServiceApp.Models
{
    public class NewsItem
    {
        public int Id { get; set; }

        [Required, StringLength(120)]
        public string Title { get; set; } = null!;

        [Required]
        public string Content { get; set; } = null!;

        [Required, StringLength(60)]
        public string Producer { get; set; } = null!;

        [Required, DataType(DataType.Date)]
        public DateTime Date { get; set; }

        [Required, StringLength(40)]
        public string Category { get; set; } = null!;   // Politics / Society / Health ...
    }
}
